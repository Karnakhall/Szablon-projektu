// Copyright 2025 Teyon. All Rights Reserved.


#include "Cars/PorscheCar.h"
#include "ChaosVehicleMovementComponent.h"

APorscheCar::APorscheCar()
{
	
	/*CarSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("CarSkeletalMesh");
	SetRootComponent(CarSkeletalMesh);
	CarSkeletalMesh->SetRelativeLocation(FVector::ZeroVector);
	CarSkeletalMesh->SetRelativeRotation(FRotator::ZeroRotator);
	CarSkeletalMesh->SetRelativeScale3D(FVector(1.0f));
	*/
	USkeletalMeshComponent* CarSkeletalMesh = GetMesh();
	CarSkeletalMesh->SetRelativeLocation(FVector::ZeroVector);
	CarSkeletalMesh->SetRelativeRotation(FRotator::ZeroRotator);
	CarSkeletalMesh->SetRelativeScale3D(FVector(1.0f));

	CarBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarBody"));
	CarBody->SetupAttachment(CarSkeletalMesh, TEXT("SK_Porsche_911_Gt3_R1"));
	CarBody->SetRelativeLocation(FVector::ZeroVector);
	CarBody->SetRelativeRotation(FRotator::ZeroRotator);
	CarBody->SetRelativeScale3D(FVector(1.0f));
	
	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(CarSkeletalMesh, TEXT("door_left"));
	DoorLeft->SetRelativeLocation(FVector::ZeroVector);
	DoorLeft->SetRelativeRotation(FRotator::ZeroRotator);
	DoorLeft->SetRelativeScale3D(FVector(1.0f));

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(CarSkeletalMesh, TEXT("door_right"));
	DoorRight->SetRelativeLocation(FVector::ZeroVector);
	DoorRight->SetRelativeRotation(FRotator::ZeroRotator);
	DoorRight->SetRelativeScale3D(FVector(1.0f));
	
	Window = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window"));
	Window->SetupAttachment(CarSkeletalMesh);

	FenderLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderLeft"));
	FenderLeft->SetupAttachment(CarSkeletalMesh, TEXT("fender_left"));
	FenderLeft->SetRelativeLocation(FVector::ZeroVector);
	FenderLeft->SetRelativeRotation(FRotator::ZeroRotator);
	FenderLeft->SetRelativeScale3D(FVector(1.0f));

	FenderRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderRight"));
	FenderRight->SetupAttachment(CarSkeletalMesh, TEXT("fender_right"));
	FenderRight->SetRelativeLocation(FVector::ZeroVector);
	FenderRight->SetRelativeRotation(FRotator::ZeroRotator);
	FenderRight->SetRelativeScale3D(FVector(1.0f));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	FrontBumper->SetupAttachment(CarSkeletalMesh, TEXT("bumper_front"));
	FrontBumper->SetRelativeLocation(FVector::ZeroVector);
	FrontBumper->SetRelativeRotation(FRotator::ZeroRotator);
	FrontBumper->SetRelativeScale3D(FVector(1.0f));

	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontHood"));
	FrontHood->SetupAttachment(CarSkeletalMesh, TEXT("hood_front"));
	FrontHood->SetRelativeLocation(FVector::ZeroVector);
	FrontHood->SetRelativeRotation(FRotator::ZeroRotator);
	FrontHood->SetRelativeScale3D(FVector(1.0f));

	RearBoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBoot"));
	RearBoot->SetupAttachment(CarSkeletalMesh, TEXT("boot_rear"));
	RearBoot->SetRelativeLocation(FVector::ZeroVector);
	RearBoot->SetRelativeRotation(FRotator::ZeroRotator);
	RearBoot->SetRelativeScale3D(FVector(1.0f));

	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumper"));
	RearBumper->SetupAttachment(CarSkeletalMesh, TEXT("bumper_rear"));
	RearBumper->SetRelativeLocation(FVector::ZeroVector);
	RearBumper->SetRelativeRotation(FRotator::ZeroRotator);
	RearBumper->SetRelativeScale3D(FVector(1.0f));

	RearSpoiler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearSpoiler"));
	RearSpoiler->SetupAttachment(CarSkeletalMesh, TEXT("spoiler_back"));
	RearSpoiler->SetRelativeLocation(FVector::ZeroVector);
	RearSpoiler->SetRelativeRotation(FRotator::ZeroRotator);
	RearSpoiler->SetRelativeScale3D(FVector(1.0f));

	RearDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearDiffuser"));
	RearDiffuser->SetupAttachment(CarSkeletalMesh, TEXT("diffuser_back"));
	RearDiffuser->SetRelativeLocation(FVector::ZeroVector);
	RearDiffuser->SetRelativeRotation(FRotator::ZeroRotator);
	RearDiffuser->SetRelativeScale3D(FVector(1.0f));

	WingMirrorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorLeft"));
	WingMirrorLeft->SetupAttachment(CarSkeletalMesh, TEXT("wing_mirror_left"));
	WingMirrorLeft->SetRelativeLocation(FVector::ZeroVector);
	WingMirrorLeft->SetRelativeRotation(FRotator::ZeroRotator);
	WingMirrorLeft->SetRelativeScale3D(FVector(1.0f));

	WingMirrorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorRight"));
	WingMirrorRight->SetupAttachment(CarSkeletalMesh, TEXT("wing_mirror_right"));
	WingMirrorRight->SetRelativeLocation(FVector::ZeroVector);
	WingMirrorRight->SetRelativeRotation(FRotator::ZeroRotator);
	WingMirrorRight->SetRelativeScale3D(FVector(1.0f));

	Wiper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wiper"));
	Wiper->SetupAttachment(CarSkeletalMesh);	// Zmienić pozycje

	FrontWheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelRight")); //Trzeba zmienić pozycję
	FrontWheelRight->SetupAttachment(CarSkeletalMesh, TEXT("wheel_front_right_spin"));
	FrontWheelRight->SetRelativeLocation(FVector::ZeroVector);
	FrontWheelRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontWheelRight->SetRelativeScale3D(FVector(1.0f));

	FrontWheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelLeft"));
	FrontWheelLeft->SetupAttachment(CarSkeletalMesh, TEXT("wheel_front_left_spin"));
	FrontWheelLeft->SetRelativeLocation(FVector::ZeroVector);
	FrontWheelLeft->SetRelativeRotation(FRotator::ZeroRotator);
	FrontWheelLeft->SetRelativeScale3D(FVector(1.0f));

	FrontWheelRightBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelRightBlur"));
	FrontWheelRightBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_front_right_spin"));
	FrontWheelRightBlur->SetRelativeLocation(FVector::ZeroVector);
	FrontWheelRightBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	FrontWheelRightBlur->SetRelativeScale3D(FVector(1.0f));

	FrontWheelLeftBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelLeftBlur"));
	FrontWheelLeftBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_front_left_spin"));
	FrontWheelLeftBlur->SetRelativeLocation(FVector::ZeroVector);
	FrontWheelLeftBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	FrontWheelLeftBlur->SetRelativeScale3D(FVector(1.0f));

	RearWheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelRight"));
	RearWheelRight->SetupAttachment(CarSkeletalMesh, TEXT("wheel_back_right_spin"));
	RearWheelRight->SetRelativeLocation(FVector::ZeroVector);
	RearWheelRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RearWheelRight->SetRelativeScale3D(FVector(1.0f));

	RearWheelRightBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelRightBlur"));
	RearWheelRightBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_back_right_spin"));
	RearWheelRightBlur->SetRelativeLocation(FVector::ZeroVector);
	RearWheelRightBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	RearWheelRightBlur->SetRelativeScale3D(FVector(1.0f));

	RearWheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelLeft"));
	RearWheelLeft->SetupAttachment(CarSkeletalMesh, TEXT("wheel_back_left_spin"));
	RearWheelLeft->SetRelativeLocation(FVector::ZeroVector);
	RearWheelLeft->SetRelativeRotation(FRotator::ZeroRotator);
	RearWheelLeft->SetRelativeScale3D(FVector(1.0f));

	RearWheelLeftBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelLeftBlur"));
	RearWheelLeftBlur->SetupAttachment(CarSkeletalMesh, TEXT("wheel_back_left_spin"));
	RearWheelLeftBlur->SetRelativeLocation(FVector::ZeroVector);
	RearWheelLeftBlur->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	RearWheelLeftBlur->SetRelativeScale3D(FVector(1.0f));

	FrontBrakeDiscRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBrakeDiscRight"));
	FrontBrakeDiscRight->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_right"));
	FrontBrakeDiscRight->SetRelativeLocation(FVector::ZeroVector);
	FrontBrakeDiscRight->SetRelativeRotation(FRotator::ZeroRotator);
	FrontBrakeDiscRight->SetRelativeScale3D(FVector(1.0f));

	FrontCaliperRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontCaliperRight"));
	FrontCaliperRight->SetupAttachment(FrontBrakeDiscRight);
	FrontCaliperRight->SetRelativeLocation(FVector::ZeroVector);
	FrontCaliperRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontCaliperRight->SetRelativeScale3D(FVector(1.0f));

	FrontBrakeDiscLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBrakeDiscLeft"));
	FrontBrakeDiscLeft->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_left"));
	FrontBrakeDiscLeft->SetRelativeLocation(FVector::ZeroVector);
	FrontBrakeDiscLeft->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontBrakeDiscLeft->SetRelativeScale3D(FVector(1.0f));

	FrontCaliperLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontCaliperLeft"));
	FrontCaliperLeft->SetupAttachment(FrontBrakeDiscLeft);
	FrontCaliperLeft->SetRelativeLocation(FVector::ZeroVector);
	FrontCaliperLeft->SetRelativeRotation(FRotator::ZeroRotator);
	FrontCaliperLeft->SetRelativeScale3D(FVector(1.0f));

	RearBrakeDiscRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBrakeDiscRight"));
	RearBrakeDiscRight->SetupAttachment(CarSkeletalMesh, TEXT("suspension_back_right"));
	RearBrakeDiscRight->SetRelativeLocation(FVector::ZeroVector);
	RearBrakeDiscRight->SetRelativeRotation(FRotator::ZeroRotator);
	RearBrakeDiscRight->SetRelativeScale3D(FVector(1.0f));

	RearCaliperRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearCaliperRight"));
	RearCaliperRight->SetupAttachment(RearBrakeDiscRight);
	RearCaliperRight->SetRelativeLocation(FVector::ZeroVector);
	RearCaliperRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RearCaliperRight->SetRelativeScale3D(FVector(1.0f));

	RearBrakeDiscLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBrakeDiscLeft"));
	RearBrakeDiscLeft->SetupAttachment(CarSkeletalMesh, TEXT("suspension_back_left"));
	RearBrakeDiscLeft->SetRelativeLocation(FVector::ZeroVector);
	RearBrakeDiscLeft->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RearBrakeDiscLeft->SetRelativeScale3D(FVector(1.0f));

	RearCaliperLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearCaliperLeft"));
	RearCaliperLeft->SetupAttachment(RearBrakeDiscLeft);
	RearCaliperLeft->SetRelativeLocation(FVector::ZeroVector);
	RearCaliperLeft->SetRelativeRotation(FRotator::ZeroRotator);
	RearCaliperLeft->SetRelativeScale3D(FVector(1.0f));

	Interior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior"));
	Interior->SetupAttachment(CarSkeletalMesh);

	CockpitConsole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CockpitConsole"));
	CockpitConsole->SetupAttachment(CarSkeletalMesh);

	Net = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Net"));
	Net->SetupAttachment(CarSkeletalMesh);

	PedalAcceleration = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalAcceleration"));
	PedalAcceleration->SetupAttachment(CarSkeletalMesh);	//zmienić pozycje

	PedalBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalBrake"));
	PedalBrake->SetupAttachment(CarSkeletalMesh);	//zmienić pozycje

	SeatNetClamps = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SeatNetClamps"));
	SeatNetClamps->SetupAttachment(CarSkeletalMesh);

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheel->SetupAttachment(CarSkeletalMesh);	//zmiewnić pozycje

	EngineComponents = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EngineComponents"));
	EngineComponents->SetupAttachment(CarSkeletalMesh);
}

void APorscheCar::BeginPlay()
{
	Super::BeginPlay();
}

void APorscheCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


