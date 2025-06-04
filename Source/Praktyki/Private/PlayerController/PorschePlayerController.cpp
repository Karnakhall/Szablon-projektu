// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PorschePlayerController.h"
#include "Cars/PorscheCar.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"

void APorschePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APorschePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		/* optionally steering wheel context
		if (bUseSteeringWheelControls && SteeringWheelInputMappingContext)
		{
			Subsystem->AddMappingContext(SteeringWheelInputMappingContext, 1);
		}*/
	}
}

void APorschePlayerController::Tick(float Delta)
{
	Super::Tick(Delta);

	//Maybe add UI with updating speed etc.
}

void APorschePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Pointer to the controlled pawn
	PorscheVehiclePawn = CastChecked<APorscheCar>(InPawn);
}
