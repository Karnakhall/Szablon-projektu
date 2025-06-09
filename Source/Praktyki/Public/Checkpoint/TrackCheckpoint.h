// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "TrackCheckpoint.generated.h"


UCLASS()
class PRAKTYKI_API ATrackCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackCheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // Komponent kolizji (Sphere Collision)
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBoxComponent* CheckpointBox;

    // Funkcja wywoływana, gdy coś nakłada się na SphereComponent
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Numer porządkowy checkpointa w kolejności przejazdu
    // Ten będzie używany do sortowania i sprawdzania kolejności
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint Settings")
    int32 CheckpointOrder;

    // Czy ten checkpoint jest linią startu/mety?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint Settings")
    bool bIsStartFinishLine;
};
