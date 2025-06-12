// Copyright 2025 Teyon. All Rights Reserved.


#include "Checkpoint/TrackCheckpoint.h"
#include "Cars/PorscheCar.h"
#include "Kismet/GameplayStatics.h"
#include "Praktyki/PraktykiGameModeBase.h"

// Sets default values
ATrackCheckpoint::ATrackCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and configure BoxComponent
    CheckpointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointBox"));
    RootComponent = CheckpointBox;

    // Set box size (change in Blueprint)
    CheckpointBox->SetBoxExtent(FVector(500, 100, 100));

    // Enable collision detection
    CheckpointBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CheckpointBox->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignoruj wszystkie kanały domyślnie
    CheckpointBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Overlapuj z Pawnami (czyli Twoim samochodem)

    // Generate Overlap events
    CheckpointBox->SetGenerateOverlapEvents(true);

    // Initialize variables
    CheckpointOrder = 0;
    bIsStartFinishLine = false;

}

// Called when the game starts or when spawned
void ATrackCheckpoint::BeginPlay()
{
    Super::BeginPlay();

    // OnOverlapBegin function for Overlap event
    CheckpointBox->OnComponentBeginOverlap.AddDynamic(this, &ATrackCheckpoint::OnOverlapBegin);
}

// Called every frame
void ATrackCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrackCheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the checkpoint registers the car's passage
    APorscheCar* PorscheCar = Cast<APorscheCar>(OtherActor);
    if (PorscheCar)
    {
        // Check if we are in GameMode
        APraktykiGameModeBase* GameMode = Cast<APraktykiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
        if (GameMode)
        {
            // Call a function in GameMode, passing itself (this checkpoint)
            GameMode->CheckpointPassed(this); // We pass 'this' - meaning a reference to ATrackCheckpoint
        }
    }
}

