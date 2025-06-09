// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/PorschePlayerController.h"
#include "Cars/PorscheCar.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UI/PorscheUI.h"
#include "Checkpoint/TrackCheckpoint.h"


APraktykiGameModeBase::APraktykiGameModeBase()
{
	DefaultPawnClass = APorscheCar::StaticClass();
	PlayerControllerClass = APorschePlayerController::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
}

void APraktykiGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Game Mode Base BeginPlay."));
    InitializeCheckpoints();
}

void APraktykiGameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Zaktualizuj CurrentLapTime tylko jeśli timer jest aktywny
    if (GetWorldTimerManager().IsTimerActive(GameTimerHandle))
    {
        CurrentLapTime = CurrentRaceTime - CurrentLapStartTime;
    }
}

void APraktykiGameModeBase::StartGame()
{
    UE_LOG(LogTemp, Log, TEXT("Game Started!"));
    
    APorschePlayerController* PC = Cast<APorschePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (!PC)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController in StartGame(). Cannot start game."));
        return;
    }
    PC->CreateCarHUD();
    // Resetowanie stanu gry przed rozpoczęciem nowej rozgrywki
    CurrentLapsCompleted = 0;
    CurrentRaceTime = 0.0f;
    BestLapTime = 0.0f;
    BestRaceTime = FLT_MAX;
    CurrentLapStartTime = GetWorld()->GetTimeSeconds(); // Ustaw czas rozpoczęcia pierwszego okrążenia
    NextCheckpointIndex = 0;
    CompletedLapTimes.Empty(); // Wyczyść czasy okrążeń dla nowej gry

    // Ustawienia trybu gry z GameInstance (bo tam są ustawiane w menu)
    UPraktykiGameInstance* GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        CurrentRaceModeType = GameInstance->SelectedRaceMode;
        TargetLaps = GameInstance->NumberOfLaps;
        TargetMaxRaceTime = GameInstance->MaxRaceTime;
        UE_LOG(LogTemp, Log, TEXT("StartGame() logic based on selected mode: %s"), *UEnum::GetValueAsString(CurrentRaceModeType));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PraktykiGameInstance in StartGame(). Using default RM_None."));
        CurrentRaceModeType = ERaceMode::RM_None;
        TargetLaps = 0;
        TargetMaxRaceTime = 0.0f;
    }

    // 3. Sprawdź tryb gry, aby uruchomić timer i HUD gry (czas/okrążenia)
    if (CurrentRaceModeType == ERaceMode::RM_Race || CurrentRaceModeType == ERaceMode::RM_Training)
    {
        UE_LOG(LogTemp, Log, TEXT("Starting Race/Training mode. Timer and Game HUD will be active."));
        GetWorldTimerManager().SetTimer(GameTimerHandle, this, &APraktykiGameModeBase::UpdateGameTimer, 0.01f, true); // Uruchom timer

        // Utwórz i dodaj HUD gry (czas, okrążenia) - BP_PorscheHUD
        if (GameHUDClass) // PorscheHUDClass to klasa BP_PorscheHUD
        {
            if (CurrentGameHUDInstance && CurrentGameHUDInstance->IsInViewport())
            {
                CurrentGameHUDInstance->RemoveFromParent();
                CurrentGameHUDInstance = nullptr;
            }
            CurrentGameHUDInstance = CreateWidget<UUserWidget>(GetWorld(), GameHUDClass);
            if (CurrentGameHUDInstance)
            {
                CurrentGameHUDInstance->AddToViewport();
                UE_LOG(LogTemp, Log, TEXT("Game HUD Widget (BP_PorscheHUD) created and added to viewport."));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create Game HUD Widget (BP_PorscheHUD)."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("GameHUDClass (BP_PorscheHUD Class) is not set in BP_PraktykiGameModeBase. Game HUD will not be displayed."));
        }
    }
    else 
    {
        UE_LOG(LogTemp, Log, TEXT("Starting Free Roam mode. No timer or Game HUD."));
        GetWorldTimerManager().ClearTimer(GameTimerHandle); // Upewnij się, że timer jest zatrzymany
        // Ukryj HUD gry, jeśli był widoczny
        if (CurrentGameHUDInstance && CurrentGameHUDInstance->IsInViewport())
        {
            CurrentGameHUDInstance->RemoveFromParent();
            CurrentGameHUDInstance = nullptr;
        }
    }
}

void APraktykiGameModeBase::EndGame()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle); // Zatrzymaj timer
    UE_LOG(LogTemp, Log, TEXT("Game Ended! Showing results screen."));
    DisplayResultsScreen(true);
}

void APraktykiGameModeBase::ReturnToMainMenu()
{
    UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void APraktykiGameModeBase::UpdateGameTimer()
{
    CurrentRaceTime += GetWorldTimerManager().GetTimerRate(GameTimerHandle);

    CheckGameEndConditions();

    // Zaktualizuj czas bieżącego okrążenia
    CurrentLapTime = GetWorld()->GetTimeSeconds() - CurrentLapStartTime;
}

void APraktykiGameModeBase::CheckGameEndConditions()
{
    // Ta zmienna będzie śledzić, czy gra powinna się zakończyć w tej klatce.
    bool bShouldGameEnd = false;

    // Sprawdzamy, czy tryb gry wymaga liczenia okrążeń (Wyścig lub Trening)
    if (CurrentRaceModeType == ERaceMode::RM_Race || CurrentRaceModeType == ERaceMode::RM_Training)
    {
        // Warunek 1: Ukończono wymaganą liczbę okrążeń.
        // TargetLaps jest poprawnie ustawiane w BeginPlay() dla obu trybów.
        if (TargetLaps > 0 && CurrentLapsCompleted >= TargetLaps)
        {
            UE_LOG(LogTemp, Log, TEXT("Game End Condition Met: All %d laps completed for mode %s."), TargetLaps, *UEnum::GetValueAsString(CurrentRaceModeType));
            bShouldGameEnd = true;
        }
    }

    // Warunek 2: Przekroczono maksymalny czas gry (jeśli jest ustawiony).
    // Ten warunek jest niezależny od liczby okrążeń.
    if (TargetMaxRaceTime > 0.0f && CurrentRaceTime >= TargetMaxRaceTime)
    {
        UE_LOG(LogTemp, Log, TEXT("Game End Condition Met: Max race time (%f) exceeded."), TargetMaxRaceTime);
        bShouldGameEnd = true;
    }

    // Jeśli którykolwiek z powyższych warunków został spełniony, zakończ grę.
    // Dzięki temu EndGame() zostanie wywołane tylko RAZ.
    if (bShouldGameEnd)
    {
        EndGame();
    }
}

void APraktykiGameModeBase::InitializeCheckpoints()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATrackCheckpoint::StaticClass(), FoundActors);
    if (FoundActors.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No ATrackCheckpoint actors found in the level. Race may not function correctly."));
    }
    else
    {
        TrackCheckpoints.Empty();
        for (AActor* Actor : FoundActors)
        {
            ATrackCheckpoint* Checkpoint = Cast<ATrackCheckpoint>(Actor);
            if (Checkpoint)
            {
                TrackCheckpoints.Add(Checkpoint);
            }
        }
    }
    // Posortuj checkpointy po ich CheckpointOrder
    TrackCheckpoints.Sort([](const ATrackCheckpoint& A, const ATrackCheckpoint& B)
        {
            return A.CheckpointOrder < B.CheckpointOrder;
        });

    // Sprawdzenie, czy pierwszy checkpoint to linia startu/mety
    if (TrackCheckpoints.IsValidIndex(0) && !TrackCheckpoints[0]->bIsStartFinishLine)
    {
        UE_LOG(LogTemp, Warning, TEXT("First checkpoint (Order 0) is not marked as Start/Finish Line!"));
    }

    UE_LOG(LogTemp, Log, TEXT("Found %d checkpoints. First checkpoint order: %d. Last checkpoint order: %d."),
        TrackCheckpoints.Num(),
        TrackCheckpoints.IsValidIndex(0) ? TrackCheckpoints[0]->CheckpointOrder : -1,
        TrackCheckpoints.IsValidIndex(TrackCheckpoints.Num() - 1) ? TrackCheckpoints.Last()->CheckpointOrder : -1
    );
}

void APraktykiGameModeBase::CheckpointPassed(ATrackCheckpoint* CheckpointActor)
{
    if (!CheckpointActor) return;

    // Sprawdź, czy to oczekiwany checkpoint
    if (TrackCheckpoints.IsValidIndex(NextCheckpointIndex) && TrackCheckpoints[NextCheckpointIndex] == CheckpointActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Passed checkpoint: Order %d"), CheckpointActor->CheckpointOrder);
        NextCheckpointIndex++;

        // Jeśli osiągnięto ostatni checkpoint (linia mety/startu)
        if (NextCheckpointIndex >= TrackCheckpoints.Num())
        {
            // Oznacza to, że gracz ukończył okrążenie
            CurrentLapsCompleted++;
            float LapDuration = CurrentRaceTime - CurrentLapStartTime;
            CompletedLapTimes.Add(LapDuration);
            UE_LOG(LogTemp, Log, TEXT("Lap %d completed in %f seconds."), CurrentLapsCompleted, LapDuration);

            // Zaktualizuj najlepszy czas okrążenia
            if (BestLapTime == 0.0f || LapDuration < BestLapTime)
            {
                BestLapTime = LapDuration;
                UE_LOG(LogTemp, Log, TEXT("New best lap time: %f"), BestLapTime);
            }

            // Zresetuj indeks checkpointów dla następnego okrążenia
            NextCheckpointIndex = 0;
            CurrentLapStartTime = CurrentRaceTime; // Ustaw początek nowego okrążenia

            CheckGameEndConditions(); // Sprawdź, czy okrążenie zakończyło grę
        }
    }
    else
    {
        // Jeśli gracz przejechał przez checkpoint w złej kolejności
        UE_LOG(LogTemp, Warning, TEXT("Passed checkpoint (Order %d) out of order. Expected: Order %d."),
            CheckpointActor->CheckpointOrder,
            TrackCheckpoints.IsValidIndex(NextCheckpointIndex) ? TrackCheckpoints[NextCheckpointIndex]->CheckpointOrder : -1
        );
    }
}

void APraktykiGameModeBase::ResetLap()
{
    NextCheckpointIndex = 0;
    CurrentLapStartTime = GetWorld()->GetTimeSeconds();
    CurrentLapTime = 0.0f;
    UE_LOG(LogTemp, Log, TEXT("Lap reset."));
}

void APraktykiGameModeBase::DisplayResultsScreen(bool bPlayerWon)
{
    // Ukryj HUD samochodu
    APorschePlayerController* PC = Cast<APorschePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (!PC)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController to display results."));
        ReturnToMainMenu(); // Fallback
        return;
    }

    TSubclassOf<UUserWidget> WidgetToDisplay = nullptr;

    if (CurrentRaceModeType == ERaceMode::RM_Race)
    {
        WidgetToDisplay = RaceResultsWidgetClass; // Użyj nowej zmiennej

    }
    else if (CurrentRaceModeType == ERaceMode::RM_Training)
    {
        WidgetToDisplay = TrainingResultsWidgetClass; // Użyj nowej zmiennej
    }

    if (WidgetToDisplay)
    {
        UUserWidget* ResultsWidget = CreateWidget<UUserWidget>(PC, WidgetToDisplay);
        if (ResultsWidget)
        {
            ResultsWidget->AddToViewport();
            PC->CurrentResultsScreenInstance = ResultsWidget; // Zapisz referencję
            PC->SetInputMode(FInputModeUIOnly());
            PC->bShowMouseCursor = true;

            UE_LOG(LogTemp, Log, TEXT("Results screen displayed for mode: %s"), *UEnum::GetValueAsString(CurrentRaceModeType));
            UE_LOG(LogTemp, Log, TEXT("Best Lap Time: %f"), BestLapTime);
            UE_LOG(LogTemp, Log, TEXT("Total Race Time: %f"), CurrentRaceTime);
            for (int32 i = 0; i < CompletedLapTimes.Num(); ++i)
            {
                UE_LOG(LogTemp, Log, TEXT("Lap %d: %f"), i + 1, CompletedLapTimes[i]);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create results widget for mode: %s! Returning to main menu."), *UEnum::GetValueAsString(CurrentRaceModeType));
            ReturnToMainMenu(); // Fallback
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Results widget class not set for current race mode. Returning to main menu."));
        ReturnToMainMenu();
    }
}



