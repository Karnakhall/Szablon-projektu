// Copyright 2025 Teyon. All Rights Reserved.
// Main player car class - inherits from AWheeledVehiclePawn

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "ChaosVehicleMovementComponent.h"
#include "PorscheCar.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API APorscheCar : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:
	APorscheCar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	/*
	*	Components
	*/

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* CarSkeletalMesh;
};

