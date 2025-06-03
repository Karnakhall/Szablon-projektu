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
	
	UPROPERTY(EditAnywhere, Category = "Car|Skeletal")
	USkeletalMeshComponent* CarSkeletalMesh;
	
	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* CarBody;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	int32 VisibleAnywhere;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* DoorLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* DoorRight;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* Window;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* FenderLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Body")
	UStaticMeshComponent* FenderRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* FrontBumper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* FrontHood;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearBoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearBumper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearSpoiler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* RearDiffuser;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* WingMirrorLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* WingMirrorRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body")
	UStaticMeshComponent* Wiper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelRightBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* FrontWheelLeftBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelRightBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelLeftBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels")
	UStaticMeshComponent* RearWheelLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontBrakeDiscRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontBrakeDiscLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearBrakeDiscRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearBrakeDiscLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontCaliperRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* FrontCaliperLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearCaliperRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes")
	UStaticMeshComponent* RearCaliperLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* Interior;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* CockpitConsole;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* Net;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* PedalAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* PedalBrake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* SeatNetClamps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* SteeringWheel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Interior")
	UStaticMeshComponent* EngineComponents;
};

