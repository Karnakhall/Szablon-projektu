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
	
	UPROPERTY(EditAnywhere, Category="Car")
	TObjectPtr<USkeletalMeshComponent> CarSkeletalMesh;
	
	UPROPERTY(EditAnywhere, Category="Car|Body|")
	UStaticMeshComponent* CarBody;

	UPROPERTY(EditAnywhere, Category="Car|Body|")
	UStaticMeshComponent* DoorLeft;

	UPROPERTY(EditAnywhere, Category="Car|Body|")
	UStaticMeshComponent* DoorRight;
	/*
	UPROPERTY(EditAnywhere, Category="Car|Body|")
	UStaticMeshComponent* Window;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* FenderLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* FenderRight;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* FrontBumper;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* FrontHood;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* RearBoot;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* RearBumper;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* RearSpoiler;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* RearDiffuser;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* WingMirrorLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* WingMirrorRight;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* Wiper;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelRight;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelRightBlur;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelLeftBlur;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelRightBlur;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelLeftBlur;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelBlur;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelRight;

	UPROPERTY(EditAnywhere, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* FrontBrakeDiscRight;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* FrontBrakeDiscLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* RearBrakeDiscRight;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* RearBrakeDiscLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* FrontCaliperRight;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* FrontCaliperLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* RearCaliperRight;

	UPROPERTY(EditAnywhere, Category = "Car|Brakes")
	UStaticMeshComponent* RearCaliperLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* Interior;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* CockpitConsole;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* Net;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* PedalAcceleration;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* PedalBrake;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* SeatNetClamps;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(EditAnywhere, Category = "Car|Interior")
	UStaticMeshComponent* EngineComponents;

	*/
};

