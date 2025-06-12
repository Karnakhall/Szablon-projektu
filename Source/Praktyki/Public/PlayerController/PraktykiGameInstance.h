// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PraktykiGameInstance.generated.h"

// Enum to store game modes
UENUM(BlueprintType)
enum class ERaceMode : uint8
{
	RM_None UMETA(DisplayName = "None"),
	RM_Training UMETA(DisplayName = "Training"),
	RM_Race	 UMETA(DisplayName = "Race")
};

/** Main game instance to store game parameters */

UCLASS()
class PRAKTYKI_API UPraktykiGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPraktykiGameInstance();

	UPROPERTY(BlueprintReadWrite, Category = "RaceSettings")
	ERaceMode SelectedRaceMode;		// Selected race mode

	UPROPERTY(BlueprintReadWrite, Category = "RaceSettings")
	int32 NumberOfLaps;		//Number of laps for race

	UPROPERTY(BlueprintReadWrite, Category = "RaceSettings")
	float MaxRaceTime;	// Max time for game

	// Initialization function, called after Game Instance is created
	virtual void Init() override;
};
