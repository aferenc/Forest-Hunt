// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class FORESTHUNT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
  
  // Base shape collision
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Collision")
  class USphereComponent* CollisionVolume;
  
  // Base mesh component
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Mesh")
  class UStaticMeshComponent* Mesh;
  
  // Particles around the item while it's on the map
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
  class UParticleSystemComponent* IdleParticlesComponent;
  
  // Particles that appear upon collision
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles")
  class UParticleSystem* OverlapParticles;
  
  // Sound effect that plays upon collision
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sounds")
  class USoundCue* OverlapSound;
  
  // Rotation flag
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | ItemProperties")
  bool bRotate;
  
  // Rotation speed
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | ItemProperties")
  float RotationRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
