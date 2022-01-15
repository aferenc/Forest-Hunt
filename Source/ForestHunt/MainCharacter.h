// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class FORESTHUNT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
  
  // Spring arm for camera
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class USpringArmComponent* CameraBoom;
  
  // Camera that follows the player character
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  class UCameraComponent* FollowCamera;
  
  /** Player stats */
  
  // The total number of collectible items on the field
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
  int32 TotalItems;
  
  // The number of collectible items collected
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
  int32 CollectedItems;
  
  // The amount of time in the countdown, in seconds
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
  int32 CountdownTime;
  /*
  // Add to the number of collected items
  UFUNCTION()
  void IncrementItems();
  
  // Advance the timer by one second
  UFUNCTION()
  void AdvanceTimer();
  
  // Win event
  UFUNCTION()
  void Win();
  
  // Loss event
  UFUNCTION()
  void Lose();
  
  // Quit to main menu mid-game
  UFUNCTION()
  void Quit();
  
  // Returns to the main menu
  UFUNCTION()
  void ReturnToMainMenu();
  
  // Handles advancing the counter every second
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
  FTimerHandle CountdownTimerHandle;
  
  // Clears the countdown timer when the player wins
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
  FTimerHandle WinMenuTimerHandle;
  
  // Clears the countdown timer when thep player runs out of time
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Countdown")
  FTimerHandle LossMenuTimerHandle;
  */
  
  // Sound effect that plays upon touching an item
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
  class USoundCue* OverlapSound;
  
  // Sound effect played during a loss
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
  class USoundCue* LossSound;
  
  // Sound effect played during a win
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
  class USoundCue* WinSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  // Called for forward/backward input
  void MoveForward(float Value);
  
  // Called for side-to-side input
  void MoveRight(float Value);
  
  /** Getters for FollowCamera and CameraBoom */
  FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
  FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
