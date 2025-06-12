// Copyright 2025 Teyon. All Rights Reserved.


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

    // Update CurrentLapTime only if the timer is activ
    if (GetWorldTimerManager().IsTimerActive(GameTimerHandle))
    {
        CurrentLapTime = CurrentRaceTime - CurrentLapStartTime;
    }
}

void APraktykiGameModeBase::StartGame()
{
    UE_LOG(LogTemp, Log, TEXT("Game Started!"));
    
    // Reset game state before starting a new game
    CurrentLapsCompleted = 0;
    CurrentRaceTime = 0.0f;
    BestLapTime = 0.0f;
    BestRaceTime = FLT_MAX;
    CurrentLapStartTime = GetWorld()->GetTimeSeconds(); // Set the start time for the first lap
    NextCheckpointIndex = 0;
    CompletedLapTimes.Empty(); // Clear lap times for a new game

    // Game mode settings from GameInstance
    UPraktykiGameInstance* GameInstance = Cast<UPraktykiGameInstance>(GetGameInstance());
    if (GameInstance)
    {
        CurrentRaceModeType = GameInstance->SelectedRaceMode;
        UE_LOG(LogTemp, Log, TEXT("GameInstance loaded. Selected mode: %s"), *UEnum::GetValueAsString(CurrentRaceModeType));

        if (CurrentRaceModeType == ERaceMode::RM_Training)
        {
            TargetLaps = 1; // Training is ALWAYS one lap
            TargetMaxRaceTime = 0.0f; // Training has no time limit
            UE_LOG(LogTemp, Log, TEXT("Game Mode: Training. Target Laps FORCED to: %d"), TargetLaps);
        }
        else if (CurrentRaceModeType == ERaceMode::RM_Race)
        {
            TargetLaps = GameInstance->NumberOfLaps; // Race retrieves the number of laps from GameInstance
            TargetMaxRaceTime = GameInstance->MaxRaceTime; // Also get the target time (even if 0)
            UE_LOG(LogTemp, Log, TEXT("Game Mode: Race. Target Laps set to: %d"), TargetLaps);
        }
    }
    
    // Check game mode to start the timer and game HUD (time/laps)
    if (CurrentRaceModeType == ERaceMode::RM_Race || CurrentRaceModeType == ERaceMode::RM_Training)
    {
        UE_LOG(LogTemp, Log, TEXT("Starting Race/Training mode. Timer and Game HUD will be active."));
        GetWorldTimerManager().SetTimer(GameTimerHandle, this, &APraktykiGameModeBase::UpdateGameTimer, 0.01f, true); // Uruchom timer

        // Create and add game HUD (time, laps)
        if (GameHUDClass) 
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
        GetWorldTimerManager().ClearTimer(GameTimerHandle); // Make sure the timer is stopped
        
        if (CurrentGameHUDInstance && CurrentGameHUDInstance->IsInViewport())
        {
            CurrentGameHUDInstance->RemoveFromParent();
            CurrentGameHUDInstance = nullptr;
        }
    }
    APorschePlayerController* PC = Cast<APorschePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (PC)
    {
        PC->SetInputMode(FInputModeGameOnly());
        PC->bShowMouseCursor = false;
        PC->CreateCarHUD();
    }
}

void APraktykiGameModeBase::EndGame()
{
    GetWorldTimerManager().ClearTimer(GameTimerHandle); // Stop the timer
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

    // Update current lap time
    CurrentLapTime = GetWorld()->GetTimeSeconds() - CurrentLapStartTime;
}

void APraktykiGameModeBase::CheckGameEndConditions()
{
    // This variable will track whether the game should end in this frame.
    bool bShouldGameEnd = false;
    // Required number of laps completed
    if (TargetLaps > 0 && CurrentLapsCompleted >= TargetLaps)
    {
        UE_LOG(LogTemp, Log, TEXT("Game End Condition Met: All %d laps completed."), TargetLaps);
        bShouldGameEnd = true;
    }

    // Maximum game time exceeded (if set)
    if (TargetMaxRaceTime > 0.0f && CurrentRaceTime >= TargetMaxRaceTime)
    {
        UE_LOG(LogTemp, Log, TEXT("Game End Condition Met: Max race time (%f) exceeded."), TargetMaxRaceTime);
        bShouldGameEnd = true;
    }

    // If any condition is met, end the game ONLY ONCE.
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
    // Sort checkpoints by their CheckpointOrder
    TrackCheckpoints.Sort([](const ATrackCheckpoint& A, const ATrackCheckpoint& B)
        {
            return A.CheckpointOrder < B.CheckpointOrder;
        });

    // Check if the first checkpoint is the start/finish line
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

    // Check if this is the expected checkpoint
    if (TrackCheckpoints.IsValidIndex(NextCheckpointIndex) && TrackCheckpoints[NextCheckpointIndex] == CheckpointActor)
    {
        UE_LOG(LogTemp, Log, TEXT("Passed checkpoint: Order %d"), CheckpointActor->CheckpointOrder);
        NextCheckpointIndex++;

        // If the last checkpoint is reached (finish/start line)
        if (NextCheckpointIndex >= TrackCheckpoints.Num())
        {
            // This means the player has completed a lap
            CurrentLapsCompleted++;
            float LapDuration = CurrentRaceTime - CurrentLapStartTime;
            CompletedLapTimes.Add(LapDuration);
            UE_LOG(LogTemp, Log, TEXT("Lap %d completed in %f seconds."), CurrentLapsCompleted, LapDuration);

            // Update best lap time
            if (BestLapTime == 0.0f || LapDuration < BestLapTime)
            {
                BestLapTime = LapDuration;
                UE_LOG(LogTemp, Log, TEXT("New best lap time: %f"), BestLapTime);
            }

            // Reset checkpoint index for the next lap
            NextCheckpointIndex = 0;
            CurrentLapStartTime = CurrentRaceTime; // Set the start of a new lap

            CheckGameEndConditions(); // Check if the lap ended the game
        }
    }
    else
    {
        // If the player drove through a checkpoint in the wrong order
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
    // Hide the car HUD
    APorschePlayerController* PC = Cast<APorschePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    if (!PC)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get PlayerController to display results."));
        ReturnToMainMenu();
        return;
    }

    TSubclassOf<UUserWidget> WidgetToDisplay = nullptr;

    if (CurrentRaceModeType == ERaceMode::RM_Race)
    {
        WidgetToDisplay = RaceResultsWidgetClass; // Use a new variable

    }
    else if (CurrentRaceModeType == ERaceMode::RM_Training)
    {
        WidgetToDisplay = TrainingResultsWidgetClass; // Use a new variable
    }

    if (WidgetToDisplay)
    {
        UUserWidget* ResultsWidget = CreateWidget<UUserWidget>(PC, WidgetToDisplay);
        if (ResultsWidget)
        {
            ResultsWidget->AddToViewport();
            PC->CurrentResultsScreenInstance = ResultsWidget; // Save reference
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
            ReturnToMainMenu();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Results widget class not set for current race mode. Returning to main menu."));
        ReturnToMainMenu();
    }
}



