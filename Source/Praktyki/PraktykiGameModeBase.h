// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerController/PraktykiGameInstance.h"
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

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void StartGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void ReturnToMainMenu();

	/** Zmienne do przechowywania stanu rozgrywki */ 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	ERaceMode CurrentRaceModeType;

	// Liczba ukończonych okrążeń
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	int32 CurrentLapsCompleted;

	// Dla treningu/kwalifikacji
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float BestLapTime; 

	// Docelowa liczba okrążeń dla bieżącej rozgrywki (ustawiana dynamicznie)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	int32 TargetLaps;

	// Docelowy maksymalny czas gry dla bieżącej rozgrywki
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float TargetMaxRaceTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float CurrentRaceTime;

	/** Zmienne dla checkpointów i okrążeń */

	// HUD blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameHUDClass;

	//Wyświetlana instacja HUDu gry (czas/okrążenia)
	UPROPERTY()
	UUserWidget* CurrentGameHUDInstance;

	// Klasa Blueprintu dla ekranu wyników wyścigu (np. BP_RaceResultsWidget)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> RaceResultsWidgetClass;

	// Klasa Blueprintu dla ekranu wyników treningu (np. BP_TrainingResultsWidget)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> TrainingResultsWidgetClass;

	// Checkpointy w obecnym okrążeniu
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoints")
	TArray<AActor*> ActiveCheckpoints;

	// Indeks następnego oczekiwanego checkpointa
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoints")
	int32 NextCheckpointIndex;

	// Czas rozpoczęcia aktualnego okrążenia
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float CurrentLapStartTime;

	// Czas trwania aktualnego okrążenia
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float CurrentLapTime;

	// Tablica do przechowywania czasów wszystkich ukończonych okrążeń
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	TArray<float> CompletedLapTimes;

	// Najlepszy czas wyścigu (suma najlepszych okrążeń lub po prostu rekord)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float BestRaceTime;

	// Funkcja wywoływana, gdy gracz przejedzie przez checkpoint
	UFUNCTION(BlueprintCallable, Category = "Checkpoints")
	void CheckpointPassed(AActor* CheckpointActor);
protected:
	FTimerHandle GameTimerHandle;
	void UpdateGameTimer();

	void CheckGameEndConditions();

	// Inicjalizacja checkpointów
	void InitializeCheckpoints();

	// Resetowanie stanu okrążenia
	void ResetLap();

	// Funkcja do wyświetlania ekranu wyników
	void DisplayResultsScreen(bool bPlayerWon);
};
