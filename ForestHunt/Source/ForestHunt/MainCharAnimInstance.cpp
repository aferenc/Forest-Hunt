// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

// Gets the owner of the animation
void UMainCharAnimInstance::NativeInitializeAnimation()
{
  if(Pawn == nullptr)
  {
    Pawn = TryGetPawnOwner();
  }
}

// Updates player character properties that determine the current animation
void UMainCharAnimInstance::UpdateAnimationProperties()
{
  if(Pawn == nullptr)
  {
    Pawn = TryGetPawnOwner();
  }
  
  if(Pawn)
  {
    FVector Speed = Pawn->GetVelocity();
    FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
    MovementSpeed = LateralSpeed.Size();
    
    bIsInAir = Pawn->GetMovementComponent()->IsFalling();
  }
}
