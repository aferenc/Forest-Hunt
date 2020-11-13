// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"
#include "MainCharacter.h"

ACollectible::ACollectible()
{
  
}

void ACollectible::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
  UE_LOG(LogTemp, Warning, TEXT("Collectible::OnOverlapBegin()"));
  
  if(OtherActor)
  {
    AMainCharacter* MainChar = Cast<AMainCharacter>(OtherActor);
    if(MainChar)
    {
      MainChar->IncrementItems();
    }
  }
}

void ACollectible::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
  UE_LOG(LogTemp, Warning, TEXT("Collectible::OnOverlapEnd()"));
}
