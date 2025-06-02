// Copyright 2025 Teyon. All Rights Reserved.
// Main player car class - inherits from AWheeledVehiclePawn

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "PorscheCar.generated.h"


class UStaticMeshComponent;
class UChaosVehicleMovementComponent;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Skeletal")
	USkeletalMeshComponent* CarSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* CarBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* DoorLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* DoorRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* Window;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* FenderLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* FenderRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* FrontBumper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* FrontHood;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearBoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearBumper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearSpoiler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearDiffuser;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* WingMirrorLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* WingMirrorRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* Wiper;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelRightBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelLeftBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelRightBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelLeftBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelBlur;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontBrakeDiscRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontBrakeDiscLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearBrakeDiscRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearBrakeDiscLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontCaliperRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontCaliperLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearCaliperRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearCaliperLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* Interior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* CockpitConsole;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* Net;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* PedalAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* PedalBrake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* SeatNetClamps;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* EngineComponents;
};

