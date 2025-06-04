// Copyright 2025 Teyon. All Rights Reserved.


#include "Wheels/PorscheWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UPorscheWheelRear::UPorscheWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;

	WheelRadius = 40.f;
	WheelWidth = 40.0f;
	FrictionForceMultiplier = 4.0f;
	SlipThreshold = 100.0f;
	SkidThreshold = 100.0f;
	MaxSteerAngle = 0.0f;
	MaxHandBrakeTorque = 6000.0f;
}
