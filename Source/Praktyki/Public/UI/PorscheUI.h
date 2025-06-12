// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PorscheUI.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API UPorscheUI : public UUserWidget
{
	GENERATED_BODY()
protected:

	// Display speed in km/h or MPH
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Vehicle)
	bool bIsMPH = false;

public:

	// Update the displayed speed
	void UpdateSpeed(float NewSpeed);

	// Update the displayed gear
	void UpdateGear(int32 NewGear);

protected:

	// Implemented in Blueprints to display the new speed
	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnSpeedUpdate(float NewSpeed);

	// Implemented in Blueprints to display the new gear
	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnGearUpdate(int32 NewGear);
};
