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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skeletal")
	USkeletalMeshComponent* CarSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* MainBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* DoorLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* DoorRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* Window;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FenderLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FenderRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontBumper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontHood;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearBoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearBumper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearSpoiler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearDiffuser;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* WingMirrorLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* WingMirrorRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* Wiper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontWheelRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontWheelLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontWheelBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearWheelBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearWheelRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearWheelLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontBrakeDiscRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontBrakeDiscLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearBrakeDiscRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearBrakeDiscLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontCaliperRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* FrontCaliperLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearCaliperRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Body")
	UStaticMeshComponent* RearCaliperLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* Interior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* CockpitConsole;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* Net;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* PedalAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* PedalBrake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* SeatNetClamps;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interior")
	UStaticMeshComponent* EngineComponents;
};

