// Copyright 2025 Teyon. All Rights Reserved.


#include "UI/PorscheUI.h"

void UPorscheUI::UpdateSpeed(float NewSpeed)
{
	// Format speed to km/h or MPH
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);

	// Handled in Blueprints
	OnSpeedUpdate(FormattedSpeed);
}

void UPorscheUI::UpdateGear(int32 NewGear)
{
	// Handled in Blueprints
	OnGearUpdate(NewGear);
}
