// Copyright 2025 Teyon. All Rights Reserved.
// Main player car class - inherits from AWheeledVehiclePawn

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "PorscheCar.generated.h"


class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UChaosWheeledVehicleMovementComponent;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PRAKTYKI_API APorscheCar : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	

public:
	APorscheCar();

	// Player Input Component
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** CameraComponents */

	// Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	// Second Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SecondSpringArm;

	// Second Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* SecondCamera;
	

	// CameraComponents Ends 

	// Cast to ChaosVehicle component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Car|Movement")
	TObjectPtr<UChaosWheeledVehicleMovementComponent> ChaosVehicleMovement;

protected:
	virtual void BeginPlay() override;

	/**	Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* SteeringAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* AccelerationAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* BrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* HandBrakeAction;

	// Toggle Camera Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ToggleCameraAction;

	// Reset Vehicle Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ResetVehicleAction;

	// Which camera is active 
	bool bCameraActive = false;

	/**	Input Actions Ends */

	/**	Handles Inputs */
	void Steering(const FInputActionValue& Value);

	void Acceleration(const FInputActionValue& Value);

	void Brake(const FInputActionValue& Value);
	void BrakeStart(const FInputActionValue& Value);
	void BrakeStop(const FInputActionValue& Value);

	void HandBrakeStart(const FInputActionValue& Value);
	void HandBrakeStop(const FInputActionValue& Value);
	
	void ToggleCamera(const FInputActionValue& Value);
	
	void ResetVehicle(const FInputActionValue& Value);

	/**	Handles Inputs Ends */

	/**	Static Mesh Components */

	UPROPERTY(EditAnywhere, Category = "Car|Body|Main")
	UStaticMeshComponent* CarBody;

	UPROPERTY(EditAnywhere, Category = "Car|Body|Doors")
	UStaticMeshComponent* DoorLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Body|Doors")
	UStaticMeshComponent* DoorRight;

	UPROPERTY(EditAnywhere, Category = "Car|Body|Main")
	UStaticMeshComponent* Window;

	UPROPERTY(EditAnywhere, Category = "Car|Body|Fender")
	UStaticMeshComponent* FenderLeft;

	UPROPERTY(EditAnywhere, Category = "Car|Body|Fender")
	UStaticMeshComponent* FenderRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Main")
	UStaticMeshComponent* FrontBumper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Main")
	UStaticMeshComponent* FrontHood;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Main")
	UStaticMeshComponent* RearBoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Main")
	UStaticMeshComponent* RearBumper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Main")
	UStaticMeshComponent* RearSpoiler;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Main")
	UStaticMeshComponent* RearDiffuser;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Mirrors")
	UStaticMeshComponent* WingMirrorLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Mirrors")
	UStaticMeshComponent* WingMirrorRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Body|Main")
	UStaticMeshComponent* Wiper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|FrontWheels")
	UStaticMeshComponent* FrontWheelRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|FrontWheels")
	UStaticMeshComponent* FrontWheelLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|FrontWheels")
	UStaticMeshComponent* FrontWheelRightBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|FrontWheels")
	UStaticMeshComponent* FrontWheelLeftBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|RearWheels")
	UStaticMeshComponent* RearWheelRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|RearWheels")
	UStaticMeshComponent* RearWheelLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|RearWheels")
	UStaticMeshComponent* RearWheelRightBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Wheels|RearWheels")
	UStaticMeshComponent* RearWheelLeftBlur;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|FrontBrakes")
	UStaticMeshComponent* FrontBrakeDiscRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|FrontBrakes")
	UStaticMeshComponent* FrontBrakeDiscLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|RearBrakes")
	UStaticMeshComponent* RearBrakeDiscRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|RearBrakes")
	UStaticMeshComponent* RearBrakeDiscLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|FrontBrakes")
	UStaticMeshComponent* FrontCaliperRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|FrontBrakes")
	UStaticMeshComponent* FrontCaliperLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|RearBrakes")
	UStaticMeshComponent* RearCaliperRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Car|Brakes|RearBrakes")
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

	/**	Static Mesh Components Ends */

	public:
		/** Returns the front spring arm subobject */
		FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
		/** Returns the front camera subobject */
		FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
		/** Returns the back spring arm subobject */
		FORCEINLINE USpringArmComponent* GetSecondSpringArm() const { return SecondSpringArm; }
		/** Returns the back camera subobject */
		FORCEINLINE UCameraComponent* GetSecondCamera() const { return SecondCamera; }
		// Returns the cast Chaos Vehicle Movement subobject
		FORCEINLINE const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }
};

