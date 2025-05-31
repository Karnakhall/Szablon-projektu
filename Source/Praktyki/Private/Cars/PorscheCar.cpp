// Copyright 2025 Teyon. All Rights Reserved.


#include "Cars/PorscheCar.h"

APorscheCar::APorscheCar()
{
	CarSkeletalMesh = GetMesh(); //CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarSkeletalMesh"));
	CarSkeletalMesh->SetRelativeLocation(FVector::ZeroVector);
	CarSkeletalMesh->SetRelativeRotation(FRotator::ZeroRotator);
	CarSkeletalMesh->SetRelativeScale3D(FVector(1.0f));
	SetRootComponent(CarSkeletalMesh);

	MainBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainBody"));
	MainBody->SetupAttachment(CarSkeletalMesh);

	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	DoorLeft->SetupAttachment(CarSkeletalMesh);

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	DoorRight->SetupAttachment(CarSkeletalMesh);

	Window = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window"));
	Window->SetupAttachment(CarSkeletalMesh);

	FenderLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderLeft"));
	FenderLeft->SetupAttachment(CarSkeletalMesh);

	FenderRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FenderRight"));
	FenderRight->SetupAttachment(CarSkeletalMesh);

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBumper"));
	FrontBumper->SetupAttachment(CarSkeletalMesh);

	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontHood"));
	FrontHood->SetupAttachment(CarSkeletalMesh);

	RearBoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBoot"));
	RearBoot->SetupAttachment(CarSkeletalMesh);

	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBumper"));
	RearBumper->SetupAttachment(CarSkeletalMesh);

	RearSpoiler = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearSpoiler"));
	RearSpoiler->SetupAttachment(CarSkeletalMesh);

	RearDiffuser = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearDiffuser"));
	RearDiffuser->SetupAttachment(CarSkeletalMesh);

	WingMirrorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorLeft"));
	WingMirrorLeft->SetupAttachment(CarSkeletalMesh);

	WingMirrorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WingMirrorRight"));
	WingMirrorRight->SetupAttachment(CarSkeletalMesh);

	Wiper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wiper"));
	Wiper->SetupAttachment(CarSkeletalMesh);

	FrontWheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelRight"));
	FrontWheelRight->SetupAttachment(CarSkeletalMesh, TEXT("wheel_front_right_spin"));
	FrontWheelRight->SetRelativeLocation(FVector::ZeroVector);
	FrontWheelRight->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontWheelRight->SetRelativeScale3D(FVector(1.0f));

	FrontWheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelLeft"));
	FrontWheelLeft->SetupAttachment(CarSkeletalMesh);

	FrontWheelBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheelBlur"));
	FrontWheelBlur->SetupAttachment(CarSkeletalMesh);

	RearWheelBlur = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelBlur"));
	RearWheelBlur->SetupAttachment(CarSkeletalMesh);

	RearWheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelRight"));
	RearWheelRight->SetupAttachment(CarSkeletalMesh);

	RearWheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearWheelLeft"));
	RearWheelLeft->SetupAttachment(CarSkeletalMesh);

	FrontBrakeDiscRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBrakeDiscRight"));
	FrontBrakeDiscRight->SetupAttachment(CarSkeletalMesh);
	FrontBrakeDiscRight->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_right"));
	FrontBrakeDiscRight->SetRelativeLocation(FVector::ZeroVector);
	FrontBrakeDiscRight->SetRelativeRotation(FRotator::ZeroRotator);
	FrontBrakeDiscRight->SetRelativeScale3D(FVector(1.0f));

	FrontBrakeDiscLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontBrakeDiscLeft"));
	FrontBrakeDiscLeft->SetupAttachment(CarSkeletalMesh);
	FrontBrakeDiscLeft->SetupAttachment(CarSkeletalMesh, TEXT("suspension_front_left"));
	FrontBrakeDiscLeft->SetRelativeLocation(FVector::ZeroVector);
	FrontBrakeDiscLeft->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	FrontBrakeDiscLeft->SetRelativeScale3D(FVector(1.0f));

	RearBrakeDiscRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBrakeDiscRight"));
	RearBrakeDiscRight->SetupAttachment(CarSkeletalMesh);

	RearBrakeDiscLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearBrakeDiscLeft"));
	RearBrakeDiscLeft->SetupAttachment(CarSkeletalMesh);

	FrontCaliperRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontCaliperRight"));
	FrontCaliperRight->SetupAttachment(CarSkeletalMesh);

	FrontCaliperLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontCaliperLeft"));
	FrontCaliperLeft->SetupAttachment(CarSkeletalMesh);

	RearCaliperRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearCaliperRight"));
	RearCaliperRight->SetupAttachment(CarSkeletalMesh);

	RearCaliperLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RearCaliperLeft"));
	RearCaliperLeft->SetupAttachment(CarSkeletalMesh);

	Interior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior"));
	Interior->SetupAttachment(CarSkeletalMesh);

	CockpitConsole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CockpitConsole"));
	CockpitConsole->SetupAttachment(CarSkeletalMesh);

	Net = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Net"));
	Net->SetupAttachment(CarSkeletalMesh);

	PedalAcceleration = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalAcceleration"));
	PedalAcceleration->SetupAttachment(CarSkeletalMesh);

	PedalBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PedalBrake"));
	PedalBrake->SetupAttachment(CarSkeletalMesh);

	SeatNetClamps = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SeatNetClamps"));
	SeatNetClamps->SetupAttachment(CarSkeletalMesh);

	SteeringWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SteeringWheel"));
	SteeringWheel->SetupAttachment(CarSkeletalMesh);

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


