// Fill out your copyright notice in the Description page of Project Settings.


#include "PraktykiGameModeBase.h"
#include "PlayerController/PorschePlayerController.h"

APraktykiGameModeBase::APraktykiGameModeBase()
{
	PlayerControllerClass = APorschePlayerController::StaticClass();
}
