// Copyright 2025 Teyon. All Rights Reserved.


#include "PlayerController/PorschePlayerController.h"
#include "Cars/PorscheCar.h"
#include "UI/PorscheUI.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Praktyki/PraktykiGameModeBase.h"

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

		// Optionally steering wheel context 
		if (bUseSteeringWheelControls && SteeringWheelInputMappingContext)
		{
			Subsystem->AddMappingContext(SteeringWheelInputMappingContext, 1);
		}
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
	if (WidgetInstance)	//Sprawdzamy czy instancja jest widoczna i czy istnieje
	{
		WidgetInstance->RemoveFromParent();
		WidgetInstance = nullptr;
	}

	// Set up input on game and hide mouse coursor
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	CreateCarHUD();
}

void APorschePlayerController::CreateCarHUD()
{
	if (PorscheUIClass && !PorscheUI) // Upewnij się, że klasa jest ustawiona i HUD nie istnieje
	{
		PorscheUI = CreateWidget<UPorscheUI>(this, PorscheUIClass);
		if (PorscheUI)
		{
			PorscheUI->AddToViewport();
			UE_LOG(LogTemp, Log, TEXT("Car HUD Widget created and added to viewport."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create PorscheUI widget."));
		}
	}
	else if (!PorscheUIClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("PorscheUIClass is not set in BP_PorschePlayerController. Car HUD will not be displayed."));
	}
	else if (PorscheUI && !PorscheUI->IsInViewport())
	{
		PorscheUI->AddToViewport(); // Jeśli już istnieje, ale nie jest w widoku
	}
}

void APorschePlayerController::DestroyCarHUD()
{
	if (PorscheUI && PorscheUI->IsInViewport())
	{
		PorscheUI->RemoveFromParent();
		PorscheUI = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Car HUD Widget destroyed."));
	}
}

void APorschePlayerController::DestroyResultsScreen()
{
	if (CurrentResultsScreenInstance && CurrentResultsScreenInstance->IsInViewport())
	{
		CurrentResultsScreenInstance->RemoveFromParent();
		CurrentResultsScreenInstance = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Results screen destroyed."));
	}
}

void APorschePlayerController::Tick(float Delta)
{
	Super::Tick(Delta);

	// UI
	if (IsValid(PorscheVehiclePawn) && IsValid(PorscheUI))
	{
		PorscheUI->UpdateSpeed(PorscheVehiclePawn->GetChaosVehicleMovement()->GetForwardSpeed());
		PorscheUI->UpdateGear(PorscheVehiclePawn->GetChaosVehicleMovement()->GetCurrentGear());
	}

	// Możesz tutaj również aktualizować GameHUD (czas/okrążenia)
	APraktykiGameModeBase* GameMode = Cast<APraktykiGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode && GameMode->CurrentGameHUDInstance)
	{
		//Cast<UPorscheUIClass>(GameMode->CurrentGameHUDInstance)->UpdateLapCount(GameMode->CurrentLapsCompleted, GameMode->TargetLaps);
	}
}

void APorschePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Pointer to the controlled pawn
	PorscheVehiclePawn = CastChecked<APorscheCar>(InPawn);
	if (PorscheVehiclePawn)
	{
		UE_LOG(LogTemp, Log, TEXT("PlayerController possessed PorscheCar."));
	}
}
