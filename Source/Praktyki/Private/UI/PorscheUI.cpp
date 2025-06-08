// Copyright 2025 Teyon. All Rights Reserved.


#include "UI/PorscheUI.h"

void UPorscheUI::UpdateSpeed(float NewSpeed)
{
	// Sformatuj prędkość do km/h lub MPH
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);

	// Obsługa w Blueprintach
	OnSpeedUpdate(FormattedSpeed);
}

void UPorscheUI::UpdateGear(int32 NewGear)
{
	// Obsługa w Blueprintach
	OnGearUpdate(NewGear);
}
