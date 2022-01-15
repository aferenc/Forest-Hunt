// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Collectible.generated.h"

/**
 * 
 */
UCLASS()
class FORESTHUNT_API ACollectible : public AItem
{
	GENERATED_BODY()
  
public:
  
  ACollectible();
  
  //**Don't need to use UFUNCTION macro on child classes when parent class already uses UFUNCTION
  
  virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
  
  virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
