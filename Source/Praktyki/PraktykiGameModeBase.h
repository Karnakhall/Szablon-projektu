// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerController/PraktykiGameInstance.h"
#include "Checkpoint/TrackCheckpoint.h"
#include "PraktykiGameModeBase.generated.h"

class UUserWidget;
class UPorscheUI;
/**
 * 
 */
UCLASS()
class PRAKTYKI_API APraktykiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APraktykiGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void StartGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void ReturnToMainMenu();

	/** Variables to store game state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	ERaceMode CurrentRaceModeType;

	// Number of completed laps
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	int32 CurrentLapsCompleted;

	// Current game time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float CurrentRaceTime;

	// For training/qualification
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float BestLapTime; 

	// Best race time (sum of best laps or just a record)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float BestRaceTime;

	// Target number of laps for the current game (set dynamically)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	int32 TargetLaps;

	// Target maximum game time for the current game
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float TargetMaxRaceTime;

	/** Variables to store game state end */

	/** Variables for checkpoints and laps */

	// HUD blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameHUDClass;

	// Displayed instance of the game HUD (time/laps)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> CurrentGameHUDInstance;

	// Blueprint class for the race results screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> RaceResultsWidgetClass;

	// Blueprint class for the training results screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> TrainingResultsWidgetClass;

	// Checkpoints in the current lap
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoints")
	TArray<ATrackCheckpoint*> TrackCheckpoints;

	// Index of the next expected checkpoint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoints")
	int32 NextCheckpointIndex;

	// Start time of the current lap
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float CurrentLapStartTime;

	// Duration of the current lap
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float CurrentLapTime;

	// Array to store times of all completed laps
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	TArray<float> CompletedLapTimes;

	// Function called when the player drives through a checkpoint
	UFUNCTION(BlueprintCallable, Category = "Checkpoints")
	void CheckpointPassed(ATrackCheckpoint* CheckpointActor);

	/** Variables for checkpoints and laps ends */

protected:
	FTimerHandle GameTimerHandle;
	void UpdateGameTimer();

	void CheckGameEndConditions();

	// Initialize checkpoints
	void InitializeCheckpoints();

	// Reset lap state
	void ResetLap();

	// Function to display the results screen
	void DisplayResultsScreen(bool bPlayerWon);
};
