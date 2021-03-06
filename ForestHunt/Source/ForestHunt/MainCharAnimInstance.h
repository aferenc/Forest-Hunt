// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FORESTHUNT_API UMainCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
  
public:
  
  // Gets the owner of the animation
  virtual void NativeInitializeAnimation() override;
  
  // Updates player character properties that determine the current animation
  UFUNCTION(BlueprintCallable, Category = "AnimationProperties")
  void UpdateAnimationProperties();
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
  float MovementSpeed;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
  bool bIsInAir;
  
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
  class APawn* Pawn;
	
};
