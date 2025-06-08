// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PraktykiGameInstance.h"

UPraktykiGameInstance::UPraktykiGameInstance()
{
	SelectedRaceMode = ERaceMode::RM_None;		
	NumberOfLaps = 3;
	MaxRaceTime = 360.f;
}

void UPraktykiGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("PraktykiGameInstance Initialized!"));
}
