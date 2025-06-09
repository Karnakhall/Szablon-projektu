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

    // Stwórz i skonfiguruj BoxComponent
    CheckpointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointBox"));
    RootComponent = CheckpointBox;

    // Ustawienie rozmiaru boxa (zmiana w Blueprintcie)
    CheckpointBox->SetBoxExtent(FVector(500, 100, 100));

    // Włączanie detekcję kolizji
    CheckpointBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CheckpointBox->SetCollisionResponseToAllChannels(ECR_Ignore); // Ignoruj wszystkie kanały domyślnie
    CheckpointBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Overlapuj z Pawnami (czyli Twoim samochodem)

    // Generuje zdarzenia Overlap
    CheckpointBox->SetGenerateOverlapEvents(true);

    // Zainicjuj zmienne
    CheckpointOrder = 0;
    bIsStartFinishLine = false;

}

// Called when the game starts or when spawned
void ATrackCheckpoint::BeginPlay()
{
    Super::BeginPlay();

    // Funkcja OnOverlapBegin do zdarzenia Overlap
    CheckpointBox->OnComponentBeginOverlap.AddDynamic(this, &ATrackCheckpoint::OnOverlapBegin);
}

// Called every frame
void ATrackCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrackCheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Sprawdzamy czy checkpoint rejestruje przejazd auta
    APorscheCar* PorscheCar = Cast<APorscheCar>(OtherActor);
    if (PorscheCar)
    {
        // Sprawdź, czy jesteśmy w GameMode
        APraktykiGameModeBase* GameMode = Cast<APraktykiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
        if (GameMode)
        {
            // Wywołaj funkcję w GameMode, przekazując siebie (ten checkpoint)
            GameMode->CheckpointPassed(this); // Przekazujemy 'this' - czyli referencję do ACheckpoint
        }
    }
}

