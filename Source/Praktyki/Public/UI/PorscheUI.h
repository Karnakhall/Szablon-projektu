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

	// Wyświetlanie prędkości w km / h lub MPH
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Vehicle)
	bool bIsMPH = false;

public:

	// Zaktualizowanie wyświetlanej prędkości
	void UpdateSpeed(float NewSpeed);

	//	Zaktualizowanie wyświetlanego biegu
	void UpdateGear(int32 NewGear);

protected:

	//	Zaimplementowane w Blueprintach do wyświetlania nowej prędkości
	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnSpeedUpdate(float NewSpeed);

	//	Zaimplementowane w Blueprintach do wyświetlania nowego biegu
	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnGearUpdate(int32 NewGear);
};
