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
    // Resetowanie stanu gry na początku poziomu
    CurrentLapsCompleted = 0;
    CurrentRaceTime = 0.0f;
    BestLapTime = 0.0f; 
    BestRaceTime = FLT_MAX; // Ustaw na maksymalną wartość, aby pierwszy czas był najlepszy
    CurrentLapStartTime = 0.0f;
    CurrentLapTime = 0.0f;
    NextCheckpointIndex = 0;
    CurrentGameHUDInstance = nullptr;
    CompletedLapTimes.Empty(); // Wyczyść czasy okrążeń

    UE_LOG(LogTemp, Log, TEXT("Game Mode Base BeginPlay."));

    UPraktykiGameInstance* GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        CurrentRaceModeType = GameInstance->SelectedRaceMode;
        TargetLaps = GameInstance->NumberOfLaps;
        TargetMaxRaceTime = GameInstance->MaxRaceTime;
        UE_LOG(LogTemp, Log, TEXT("Game Mode Base initialized from GameInstance. Current Mode: %s, Laps: %d, Max Time: %.1f"),
            *UEnum::GetValueAsString(CurrentRaceModeType), TargetLaps, TargetMaxRaceTime);

        /*if (CurrentRaceModeType == ERaceMode::RM_Training)
        {
             
            TargetLaps = 1;     // Trening zawsze 1 okrążenie
            TargetMaxRaceTime = 0.0f;   // Trening brak limitu czasowego
            UE_LOG(LogTemp, Log, TEXT("Game Mode: Training. Target Laps: %d, No time limit."), TargetLaps);  // Ustawiamy 0.0f, a CheckGameEndConditions zignoruje to.
        }
        else if (CurrentRaceModeType == ERaceMode::RM_Race)
        {
           
            TargetLaps = GameInstance->NumberOfLaps;     // Wyścig liczba okrążeń z menu
            TargetMaxRaceTime = 0.0f;   // Wyścig brak limitu czasowego 

            // Czas będzie mierzony, ale nie będzie kończył gry.
            UE_LOG(LogTemp, Log, TEXT("Game Mode: Race. Target Laps: %d, Time will be measured, but no time limit."), TargetLaps);
        }
        else
        {
            // Domyślne zachowanie, jeśli tryb nie jest wybrany
            TargetLaps = 1;
            TargetMaxRaceTime = 0.0f; // Bez limitu czasu dla domyślnego trybu
            CurrentRaceModeType = ERaceMode::RM_Training;
            UE_LOG(LogTemp, Warning, TEXT("No game mode selected. Defaulting to Training with %d lap and no time limit."), TargetLaps);
        }*/
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PraktykiGameInstance!"));
        // Jeśli GameInstance nie został pobrany
        CurrentRaceModeType = ERaceMode::RM_None;
        TargetLaps = 0;
        TargetMaxRaceTime = 0.0f; 
    }

    InitializeCheckpoints(); // Zainicjuj checkpointy na starcie
    // StartGame(); is initialized in BP_PorscheUI
}

void APraktykiGameModeBase::StartGame()
{
    UE_LOG(LogTemp, Log, TEXT("StartGame() called in GameMode."));
    // Ustawienie timera na UpdateGameTimer co 0.01 sekundy dla dokładniejszego mierzenia czasu
    GetWorldTimerManager().SetTimer(GameTimerHandle, this, &APraktykiGameModeBase::UpdateGameTimer, 0.01f, true);
    
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
    /*
    if (GameHUDClass)
    {
        UUserWidget* HUDWidget = CreateWidget<UUserWidget>(GetWorld(), GameHUDClass);
        if (HUDWidget)
        {
            HUDWidget->AddToViewport();
            UE_LOG(LogTemp, Log, TEXT("Game HUD Widget created and added to viewport."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameHUDWidgetClass is not set in GameMode. HUD will not be displayed."));
    }*/
}

void APraktykiGameModeBase::EndGame()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle); // Zatrzymaj timer
    UE_LOG(LogTemp, Log, TEXT("Game Ended! Player won"));

    // Ukryj HUD gry (jeśli jest widoczny)
    if (CurrentGameHUDInstance && CurrentGameHUDInstance->IsInViewport())
    {
        CurrentGameHUDInstance->RemoveFromParent();
        CurrentGameHUDInstance = nullptr;
    }

    // Ukryj HUD samochodu
    APorschePlayerController* PC = Cast<APorschePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (PC)
    {
        PC->DestroyCarHUD(); // Wywołaj funkcję z PlayerController
    }

    // Wyświetl ekran wyników
    DisplayResultsScreen(true);
}

void APraktykiGameModeBase::ReturnToMainMenu()
{
    // Ukryj wszelkie pozostałe HUDy i ekrany wyników, zanim załadujemy nową mapę
    APorschePlayerController* PC = Cast<APorschePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (PC)
    {
        PC->DestroyCarHUD();
        // Jeśli PC również ma funkcję do ukrywania ekranów wyników, wywołaj ją
        PC->DestroyResultsScreen(); // Musimy dodać tę funkcję do PlayerController
    }
    if (CurrentGameHUDInstance && CurrentGameHUDInstance->IsInViewport())
    {
        CurrentGameHUDInstance->RemoveFromParent();
        CurrentGameHUDInstance = nullptr;
    }
    UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void APraktykiGameModeBase::UpdateGameTimer()
{
    CurrentRaceTime = GetWorld()->GetTimeSeconds() - CurrentLapStartTime; // Czas od rozpoczęcia okrążenia/gry

    CheckGameEndConditions();
}

void APraktykiGameModeBase::CheckGameEndConditions()
{
    // Warunki zakończenia gry tylko dla trybów Race i Training
    if (CurrentRaceModeType == ERaceMode::RM_Race || CurrentRaceModeType == ERaceMode::RM_Training)
    {
        bool bLapsCompleted = (TargetLaps > 0 && CurrentLapsCompleted >= TargetLaps);
        bool bTimeExpired = (TargetMaxRaceTime > 0.0f && CurrentRaceTime >= TargetMaxRaceTime);

        if (bLapsCompleted || bTimeExpired)
        {
            EndGame();
        }
    }
}

void APraktykiGameModeBase::InitializeCheckpoints()
{
    ActiveCheckpoints.Empty();
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Checkpoint"), FoundActors);

   /*// Sortujemy checkpointy po ich nazwach/numerach, aby zachować kolejność
    // Zakładamy, że checkpointy są nazwane "Checkpoint_0", "Checkpoint_1", ..., "Checkpoint_N"
    FoundActors.Sort([](const AActor& A, const AActor& B)
        {
            FString NameA = A.GetName();
            FString NameB = B.GetName();
            int32 NumA, NumB;
            NameA.RemoveFromStart("Checkpoint_");
            NameB.RemoveFromStart("Checkpoint_");
            // Zakładamy, że konwersja do int jest bezpieczna
            FCString::Atoi(*NameA);
            FCString::Atoi(*NameB);
            return FCString::Atoi(*NameA) < FCString::Atoi(*NameB);
        });

    // Sprawdź, czy pierwszy checkpoint to "StartLine"
    AActor* StartLine = nullptr;
    TArray<AActor*> FoundStartLines;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("StartLine"), FoundStartLines);
    if (FoundStartLines.Num() > 0)
    {
        StartLine = FoundStartLines[0];
        // Upewnij się, że StartLine jest na początku listy ActiveCheckpoints
        // Możesz albo dodać go na początek, albo upewnić się, że to pierwszy tag "Checkpoint"
        // Jeśli używasz tagu "StartLine" jako pierwszego checkpointa, po prostu dodaj go
        ActiveCheckpoints.Add(StartLine);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No actor with tag 'StartLine' found! Checkpoint system might not work correctly."));
    }
    */
    for (AActor* Actor : FoundActors)
    {
        ATrackCheckpoint* Checkpoint = Cast<ATrackCheckpoint>(Actor);
        if (Checkpoint)
        {
            ActiveCheckpoints.Add(Checkpoint);
        }
    }

    // Sortuj checkpointy po ich numerze porządkowym (CheckpointOrder)
    ActiveCheckpoints.Sort([](const ATrackCheckpoint& A, const ATrackCheckpoint& B)
        {
            return A.CheckpointOrder < B.CheckpointOrder;
        });

    // Dodatkowo, sprawdzamy, czy pierwszy checkpoint to faktycznie linia startu
    if (ActiveCheckpoints.Num() > 0 && !ActiveCheckpoints[0]->bIsStartFinishLine)
    {
        UE_LOG(LogTemp, Warning, TEXT("First checkpoint (%s) is not marked as Start/Finish Line (bIsStartFinishLine = true). Please set it in Blueprint."), *ActiveCheckpoints[0]->GetName());
    }


    if (ActiveCheckpoints.Num() > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Initialized %d checkpoints using ACheckpoint class."), ActiveCheckpoints.Num());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No ACheckpoint actors found in the level. Race may not function correctly."));
    }
}

void APraktykiGameModeBase::CheckpointPassed(ATrackCheckpoint* CheckpointActor)
{
    // Upewnij się, że to tryb wyścigu lub treningu
    if (CurrentRaceModeType == ERaceMode::RM_None)
    {
        return;
    }

    // Sprawdź, czy przekroczony checkpoint jest tym, którego oczekujemy
    if (ActiveCheckpoints.IsValidIndex(NextCheckpointIndex) && ActiveCheckpoints[NextCheckpointIndex] == CheckpointActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Checkpoint %d (%s) passed."), NextCheckpointIndex, *CheckpointActor->GetName());

        // Jeśli to jest ostatni checkpoint (linia mety)
        if (CheckpointActor->bIsStartFinishLine) // Teraz sprawdzamy flagę bIsStartFinishLine
        {
            // Oznacza ukończenie okrążenia
            CurrentLapsCompleted++;
            float LapDuration = GetWorld()->GetTimeSeconds() - CurrentLapStartTime;
            CompletedLapTimes.Add(LapDuration);
            CurrentLapTime = LapDuration; // Aktualny czas okrążenia

            if (BestLapTime == 0.0f || LapDuration < BestLapTime)
            {
                BestLapTime = LapDuration;
                UE_LOG(LogTemp, Log, TEXT("New Best Lap Time: %f"), BestLapTime);
            }
            UE_LOG(LogTemp, Log, TEXT("Lap %d completed in %f seconds. Total Laps: %d / %d"), CurrentLapsCompleted, LapDuration, CurrentLapsCompleted, TargetLaps);

            // Sprawdzamy warunki zakończenia gry
            if (CurrentLapsCompleted >= TargetLaps && TargetLaps > 0)
            {
                EndGame();
                return;
            }

            // Resetujemy na początek następnego okrążenia
            NextCheckpointIndex = 0;
            CurrentLapStartTime = GetWorld()->GetTimeSeconds(); // Zresetuj czas startu okrążenia
            UE_LOG(LogTemp, Log, TEXT("Starting new lap. Next checkpoint expected: %s (Order: %d)"),
                ActiveCheckpoints.IsValidIndex(NextCheckpointIndex) ? *ActiveCheckpoints[NextCheckpointIndex]->GetName() : TEXT("N/A"),
                ActiveCheckpoints.IsValidIndex(NextCheckpointIndex) ? ActiveCheckpoints[NextCheckpointIndex]->CheckpointOrder : -1);
        }
        else
        {
            // Przejdź do następnego checkpointa
            NextCheckpointIndex++;
            UE_LOG(LogTemp, Log, TEXT("Moving to next checkpoint. Next expected: %s (Order: %d)"),
                ActiveCheckpoints.IsValidIndex(NextCheckpointIndex) ? *ActiveCheckpoints[NextCheckpointIndex]->GetName() : TEXT("N/A"),
                ActiveCheckpoints.IsValidIndex(NextCheckpointIndex) ? ActiveCheckpoints[NextCheckpointIndex]->CheckpointOrder : -1);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Wrong checkpoint passed: %s (Order: %d). Expected: %s (Order: %d)"),
            *CheckpointActor->GetName(), CheckpointActor->CheckpointOrder,
            ActiveCheckpoints.IsValidIndex(NextCheckpointIndex) ? *ActiveCheckpoints[NextCheckpointIndex]->GetName() : TEXT("N/A"),
            ActiveCheckpoints.IsValidIndex(NextCheckpointIndex) ? ActiveCheckpoints[NextCheckpointIndex]->CheckpointOrder : -1);
        // Możesz dodać logikę kary (np. ResetLap())
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
    APorschePlayerController* PC = Cast<APorschePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (!PC)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController to display results."));
        return;
    }

    TSubclassOf<UUserWidget> WidgetToDisplay = nullptr;

    if (CurrentRaceModeType == ERaceMode::RM_Race)
    {
        WidgetToDisplay = RaceResultsWidgetClass;
        BestRaceTime = CurrentRaceTime;
    }
    else if (CurrentRaceModeType == ERaceMode::RM_Training)
    {
        WidgetToDisplay = TrainingResultsWidgetClass;
    }

    if (WidgetToDisplay)
    {
        UUserWidget* ResultsWidget = CreateWidget<UUserWidget>(PC, WidgetToDisplay);
        if (ResultsWidget)
        {
            ResultsWidget->AddToViewport();
            PC->SetInputMode(FInputModeUIOnly());
            PC->bShowMouseCursor = true;

            // TODO: Przekaż dane do widgetu wyników
            // Będziesz musiał stworzyć BlueprintCallable funkcje w tych widgetach
            // np. ResultsWidget->Execute_SetRaceResults(ResultsWidget, CurrentRaceTime, CompletedLapTimes, BestLapTime);
            // Ale na razie, po prostu wyświetl ekran.
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
            UE_LOG(LogTemp, Error, TEXT("Failed to create Results Widget."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Results Widget Class is not set for %s mode in GameMode."), *UEnum::GetValueAsString(CurrentRaceModeType));
    }
}



