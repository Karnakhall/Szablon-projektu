// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PorschePlayerController.generated.h"


class UInputMappingContext;
class APorscheCar;
class UPorscheUI;
class UUserWidget;

/**
 * 
 */

UCLASS()
class PRAKTYKI_API APorschePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	// Input Mapping Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Pointer to controlled vehicle
	TObjectPtr<APorscheCar> PorscheVehiclePawn;

	// Optional steering wheel input mapping context will be registered
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	bool bUseSteeringWheelControls = false;

	// Optional Input Mapping Context to be used for steering wheel input.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (EditCondition = "bUseSteeringWheelControls"))
	UInputMappingContext* SteeringWheelInputMappingContext; 

	// Below will be UI for the car, maybe.
	// Type of the UI to spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UPorscheUI> PorscheUIClass;

	// Pointer to the UI widget
	TObjectPtr<UPorscheUI> PorscheUI;

	// Blueprint main menu class   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidget;

	// Instancja menu głównego
	UPROPERTY()
	TObjectPtr<UUserWidget> WidgetInstance;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:

	// Function for showing main menu
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowMenu();

	// Function for hiding main menu
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideMenu();

	// Funkcje do zarządzania HUDem samochodu (PorscheUI)
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateCarHUD();

	// Funkcja do niszczenia HUDu
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DestroyCarHUD();

	// Instancja ekranu wyników (aby móc go zniszczyć)
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentResultsScreenInstance;

	// Funkcja do niszczenia ekranu wyników
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DestroyResultsScreen();

	virtual void Tick(float Delta) override;

protected:

	virtual void OnPossess(APawn* InPawn) override;

};
