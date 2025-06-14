// Copyright 2025 Teyon. All Rights Reserved.


#include "Cars/PorscheCar.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Wheels/PorscheWheelFront.h"
#include "Wheels/PorscheWheelRear.h"
#include "ChaosWheeledVehicleMovementComponent.h"

APorscheCar::APorscheCar()
{
	// Set SkeletalMesh
	USkeletalMeshComponent* CarSkeletalMesh = GetMesh();
	check(CarSkeletalMesh);

	CarSkeletalMesh->SetSimulatePhysics(true);
	CarSkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CarSkeletalMesh->SetCollisionProfileName(TEXT("Vehicle"));
	

	// Set SpringArm and Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CarSkeletalMesh);
	SpringArm->TargetArmLength = 750.0f;
	SpringArm->SocketOffset.Z = 250.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 15.0f;
	SpringArm->CameraLagMaxDistance = 50.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bAutoActivate = true;

	// Set SecondSpringArm and camera
	SecondSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Second Spring Arm"));
	SecondSpringArm->SetupAttachment(GetMesh());
	SecondSpringArm->TargetArmLength = 10.0f;
	SecondSpringArm->SocketOffset.Z = 10.0f;
	SecondSpringArm->bDoCollisionTest = false;
	SecondSpringArm->bInheritPitch = false;
	SecondSpringArm->bInheritRoll = false;
	SecondSpringArm->bEnableCameraRotationLag = true;
	SecondSpringArm->CameraRotationLagSpeed = 15.0f;
	SecondSpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	SecondCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Second Camera"));
	SecondCamera->SetupAttachment(SecondSpringArm);
	// Get Chaos Wheeled Movement component
	ChaosVehicleMovement = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());
	GetVehicleMovement()->SetUpdatedComponent(CarSkeletalMesh);

	CarBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarBody"));
	CarBody->SetupAttachment(CarSkeletalMesh, TEXT("SK_Porsche_911_Gt3_R1"));	
	CarBody->SetRelativeLocation(FVector::ZeroVector);
	CarBody->SetRelativeRotation(FRotator::ZeroRotator);
	CarBody->SetRelativeScale3D(FVector(1.0f));
	CarBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(CarSkeletalMesh, TEXT("door_left")); 
	DoorLeft->SetRelativeRotation(FRotator::ZeroRotator);
	DoorLeft->SetRelativeScale3D(FVector(1.0f));
	DoorLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(CarSkeletalMesh, TEXT("door_right"));		
	DoorRight->SetRelativeRotation(FRotator::ZeroRotator);
	DoorRight->SetRelativeScale3D(FVector(1.0f));
	DoorLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Window = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window"));
	Window->SetupAttachment(CarSkeletalMesh);
	Window->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FenderLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderLeft"));
	FenderLeft->SetupAttachment(CarSkeletalMesh, TEXT("fender_left"));
	FenderLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FenderRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderRight"));
	FenderRight->SetupAttachment(CarSkeletalMesh, TEXT("fender_right"));
	FenderRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	FrontBumper->SetupAttachment(CarSkeletalMesh, TEXT("bumper_front"));
	FrontBumper->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontHood"));
	FrontHood->SetupAttachment(CarSkeletalMesh, TEXT("hood_front"));
	FrontHood->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearBoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBoot"));
	RearBoot->SetupAttachment(CarSkeletalMesh, TEXT("boot_rear"));
	RearBoot->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumper"));
	RearBumper->SetupAttachment(CarSkeletalMesh, TEXT("bumper_rear"));
	RearBumper->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearSpoiler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearSpoiler"));
	RearSpoiler->SetupAttachment(CarSkeletalMesh, TEXT("spoiler_back"));
	RearSpoiler->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearDiffuser"));
	RearDiffuser->SetupAttachment(CarSkeletalMesh, TEXT("diffuser_back"));
	RearDiffuser->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WingMirrorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorLeft"));
	WingMirrorLeft->SetupAttachment(CarSkeletalMesh, TEXT("wing_mirror_left"));
	WingMirrorLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WingMirrorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorRight"));
	WingMirrorRight->SetupAttachment(CarSkeletalMesh, TEXT("wing_mirror_right"));
	WingMirrorRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Wiper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wiper"));
	Wiper->SetupAttachment(CarBody, TEXT("WiperSocket"));	
	Wiper->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontWheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelRight")); 
	FrontWheelRight->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_right"));
	FrontWheelRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontWheelRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontWheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelLeft"));
	FrontWheelLeft->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_left"));
	FrontWheelLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontWheelRightBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelRightBlur"));
	FrontWheelRightBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_front_right_spin"));
	FrontWheelRightBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	FrontWheelLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontWheelLeftBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelLeftBlur"));
	FrontWheelLeftBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_front_left_spin"));
	FrontWheelLeftBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	FrontWheelLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearWheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelRight"));
	RearWheelRight->SetupAttachment(CarSkeletalMesh, TEXT("suspension_back_right"));
	RearWheelRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RearWheelRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearWheelRightBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelRightBlur"));
	RearWheelRightBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_back_right_spin"));
	RearWheelRightBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	RearWheelRightBlur->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearWheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelLeft"));
	RearWheelLeft->SetupAttachment(CarSkeletalMesh, TEXT("suspension_back_left"));
	RearWheelLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearWheelLeftBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelLeftBlur"));
	RearWheelLeftBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_back_left_spin"));
	RearWheelLeftBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	RearWheelLeftBlur->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontBrakeDiscRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBrakeDiscRight"));
	FrontBrakeDiscRight->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_right"));
	FrontBrakeDiscRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontCaliperRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontCaliperRight"));
	FrontCaliperRight->SetupAttachment(FrontBrakeDiscRight);
	FrontCaliperRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontCaliperRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontBrakeDiscLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBrakeDiscLeft"));
	FrontBrakeDiscLeft->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_left"));
	FrontBrakeDiscLeft->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontBrakeDiscLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontCaliperLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontCaliperLeft"));
	FrontCaliperLeft->SetupAttachment(FrontBrakeDiscLeft);
	FrontCaliperLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearBrakeDiscRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBrakeDiscRight"));
	RearBrakeDiscRight->SetupAttachment(CarSkeletalMesh, TEXT("suspension_back_right"));
	RearBrakeDiscRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearCaliperRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearCaliperRight"));
	RearCaliperRight->SetupAttachment(RearBrakeDiscRight);
	RearCaliperRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RearCaliperRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearBrakeDiscLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBrakeDiscLeft"));
	RearBrakeDiscLeft->SetupAttachment(CarSkeletalMesh, TEXT("suspension_back_left"));
	RearBrakeDiscLeft->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RearBrakeDiscLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RearCaliperLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearCaliperLeft"));
	RearCaliperLeft->SetupAttachment(RearBrakeDiscLeft);
	RearCaliperLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Interior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior"));
	Interior->SetupAttachment(CarSkeletalMesh);
	Interior->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CockpitConsole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CockpitConsole"));
	CockpitConsole->SetupAttachment(CarSkeletalMesh);
	CockpitConsole->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Net = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Net"));
	Net->SetupAttachment(CarSkeletalMesh);
	Net->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SeatNetClamps = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SeatNetClamps"));
	SeatNetClamps->SetupAttachment(CarSkeletalMesh);
	SeatNetClamps->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PedalAcceleration = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalAcceleration"));
	PedalAcceleration->SetupAttachment(SeatNetClamps, TEXT("PedalAccelerationSocket"));
	PedalAcceleration->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PedalBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalBrake"));
	PedalBrake->SetupAttachment(SeatNetClamps, TEXT("PedalBrakeSocket"));	
	PedalBrake->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheel->SetupAttachment(CockpitConsole, TEXT("SteeringWheelSocket"));
	SteeringWheel->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	EngineComponents = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EngineComponents"));
	EngineComponents->SetupAttachment(CarSkeletalMesh);
	EngineComponents->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set up the chassis
	GetChaosVehicleMovement()->ChassisHeight = 144.0f;
	GetChaosVehicleMovement()->DragCoefficient = 0.31f;

	//Set up wheels
	GetChaosVehicleMovement()->bLegacyWheelFrictionPosition = true;
	GetChaosVehicleMovement()->WheelSetups.SetNum(4);

	GetChaosVehicleMovement()->WheelSetups[0].WheelClass = UPorscheWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[0].BoneName = FName("suspension_front_left");
	GetChaosVehicleMovement()->WheelSetups[0].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[1].WheelClass = UPorscheWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[1].BoneName = FName("suspension_front_right");
	GetChaosVehicleMovement()->WheelSetups[1].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[2].WheelClass = UPorscheWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[2].BoneName = FName("suspension_back_left");
	GetChaosVehicleMovement()->WheelSetups[2].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[3].WheelClass = UPorscheWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[3].BoneName = FName("suspension_back_right");
	GetChaosVehicleMovement()->WheelSetups[3].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	// Set up the engine
	// NOTE: Check the Blueprint asset for the Torque Curve
	GetChaosVehicleMovement()->EngineSetup.MaxTorque = 750.0f;
	GetChaosVehicleMovement()->EngineSetup.MaxRPM = 7000.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineIdleRPM = 900.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineBrakeEffect = 0.2f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevUpMOI = 5.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevDownRate = 600.0f;

	// Set up the transmission
	GetChaosVehicleMovement()->TransmissionSetup.bUseAutomaticGears = true;
	GetChaosVehicleMovement()->TransmissionSetup.bUseAutoReverse = true;
	GetChaosVehicleMovement()->TransmissionSetup.FinalRatio = 2.81f;
	GetChaosVehicleMovement()->TransmissionSetup.ChangeUpRPM = 6000.0f;
	GetChaosVehicleMovement()->TransmissionSetup.ChangeDownRPM = 2000.0f;
	GetChaosVehicleMovement()->TransmissionSetup.GearChangeTime = 0.2f;
	GetChaosVehicleMovement()->TransmissionSetup.TransmissionEfficiency = 0.9f;

	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios.SetNum(5);
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[0] = 4.25f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[1] = 2.52f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[2] = 1.66f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[3] = 1.22f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[4] = 1.0f;

	GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios.SetNum(1);
	GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios[0] = 4.04f;

	// Set up the steering
	GetChaosVehicleMovement()->SteeringSetup.SteeringType = ESteeringType::Ackermann;
	GetChaosVehicleMovement()->SteeringSetup.AngleRatio = 0.7f;
}

void APorscheCar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Steering
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &APorscheCar::Steering);
		EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &APorscheCar::Steering);

		// Acceleration
		EnhancedInputComponent->BindAction(AccelerationAction, ETriggerEvent::Triggered, this, &APorscheCar::Acceleration);
		EnhancedInputComponent->BindAction(AccelerationAction, ETriggerEvent::Completed, this, &APorscheCar::Acceleration);

		// Brake
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &APorscheCar::Brake);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &APorscheCar::BrakeStart);
		EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &APorscheCar::BrakeStop);

		// HandBrake
		EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Started, this, &APorscheCar::HandBrakeStart);
		EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Completed, this, &APorscheCar::HandBrakeStop);

		// Toggle camera 
		EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &APorscheCar::ToggleCamera);

		// Reset the vehicle 
		EnhancedInputComponent->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &APorscheCar::ResetVehicle);
	}
}

void APorscheCar::BeginPlay()
{
	Super::BeginPlay();
}

void APorscheCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Angular damping
	bool bMovingOnGround = ChaosVehicleMovement->IsMovingOnGround();
	GetMesh()->SetAngularDamping(bMovingOnGround ? 0.0f : 3.0f);
}

void APorscheCar::Steering(const FInputActionValue& Value)
{
	// Input magnitude for steering
	float SteeringValue = Value.Get<float>();

	// Input
	ChaosVehicleMovement->SetSteeringInput(SteeringValue);
}

void APorscheCar::Acceleration(const FInputActionValue& Value)
{
	// Input magnitude for the Acceleration
	float AccelerationValue = Value.Get<float>();

	// Input
	ChaosVehicleMovement->SetThrottleInput(AccelerationValue);
}

void APorscheCar::Brake(const FInputActionValue& Value)
{
	// Input magnitude for the brakes
	float BreakValue = Value.Get<float>();

	// Input
	ChaosVehicleMovement->SetBrakeInput(BreakValue);
}

void APorscheCar::BrakeStart(const FInputActionValue& Value)
{

}

void APorscheCar::BrakeStop(const FInputActionValue& Value)
{
	// Reset input to zero
	ChaosVehicleMovement->SetBrakeInput(0.0f);
}

void APorscheCar::HandBrakeStart(const FInputActionValue& Value)
{
	// Input
	ChaosVehicleMovement->SetHandbrakeInput(true);
}

void APorscheCar::HandBrakeStop(const FInputActionValue& Value)
{
	// Input
	ChaosVehicleMovement->SetHandbrakeInput(false);
}

void APorscheCar::ToggleCamera(const FInputActionValue& Value)
{
	// toggle the active camera flag
	bCameraActive = !bCameraActive;

	Camera->SetActive(bCameraActive);
	SecondCamera->SetActive(!bCameraActive);
}

void APorscheCar::ResetVehicle(const FInputActionValue& Value)
{
	// reset to a location slightly above our current one
	FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	// reset to our yaw. Ignore pitch and roll
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;

	// teleport the actor to the reset spot and reset physics
	SetActorTransform(FTransform(ResetRotation, ResetLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	//UE_LOG(LogTemplateVehicle, Error, TEXT("Reset Vehicle"));
}
