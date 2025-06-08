// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PraktykiGameInstance.h"

UPraktykiGameInstance::UPraktykiGameInstance()
{
	SelectedRaceMode = ERaceMode::RM_Training;		// 
	NumberOfLaps = 1.f;
	MaxRaceTime = 360.f;
}

void UPraktykiGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("PraktykiGameInstance Initialized!"));
}
