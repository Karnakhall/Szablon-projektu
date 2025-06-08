// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerController/PraktykiGameInstance.h"
#include "PraktykiGameModeBase.generated.h"

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

	// Zmienne do przechowywania stanu rozgrywki
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	ERaceMode CurrentRaceModeType;

	// Liczba ukończonych okrążeń
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	int32 CurrentLapsCompleted;

	// Dla treningu/kwalifikacji
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float BestLapTime; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PorscheHUD;

	// Docelowa liczba okrążeń dla bieżącej rozgrywki (ustawiana dynamicznie)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	int32 TargetLaps;

	// Docelowy maksymalny czas gry dla bieżącej rozgrywki
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float TargetMaxRaceTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	float CurrentRaceTime;

protected:
	FTimerHandle GameTimerHandle;
	void UpdateGameTimer();

	void CheckGameEndConditions();
};
