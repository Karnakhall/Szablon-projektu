// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PorschePlayerController.h"
#include "Cars/PorscheCar.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Blueprint/UserWidget.h"

void APorschePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetMapName().Contains(TEXT("TestMap")))
	{
		ShowMenu();
	}
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

void APorschePlayerController::ShowMenu()
{
	// Check if we have the Widget Blueprint class assigned
	if (MainMenuWidget)
	{
		if (WidgetInstance)
		{
			WidgetInstance->RemoveFromParent();
			WidgetInstance = nullptr;
		}

		WidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidget);
		if (WidgetInstance)
		{
			WidgetInstance->AddToViewport();

			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MainMenuWidget is not set in PorschePlayerController Blueprint"));
	}
}

void APorschePlayerController::HideMenu()
{
	if (WidgetInstance)
	{
		WidgetInstance->RemoveFromParent();
		WidgetInstance = nullptr;
	}

	// Set up input on game and hide mouse coursor
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
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
