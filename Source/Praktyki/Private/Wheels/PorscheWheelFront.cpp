// Copyright 2025 Teyon. All Rights Reserved.


#include "Wheels/PorscheWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UPorscheWheelFront::UPorscheWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;

	WheelRadius = 39.0f;
	WheelWidth = 35.0f;
	FrictionForceMultiplier = 3.0f;

	MaxBrakeTorque = 4500.0f;
	MaxHandBrakeTorque = 6000.0f;
}
