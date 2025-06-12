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

    // Collision component
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UBoxComponent* CheckpointBox;

    // Function called when something overlaps the SphereComponent
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    // Checkpoint's sequential number in driving order
    // This will be used for sorting and checking order
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint Settings")
    int32 CheckpointOrder;

    // Is this checkpoint the start/finish line?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint Settings")
    bool bIsStartFinishLine;
};
