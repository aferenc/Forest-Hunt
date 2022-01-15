// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ForestHuntGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FORESTHUNT_API AForestHuntGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
  
public:
  
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
  
  // Add to the number of collected items
  void IncrementItems();
  
  // Advance the timer by one second
  void AdvanceTimer();
  
  // Win event
  void Win();
  
  // Loss event
  void Lose();
  
  // Quit to main menu mid-game
  void Quit();
  
  // Returns to the main menu
  void ReturnToMainMenu();
  
  // Handles advancing the counter every second
  FTimerHandle CountdownTimerHandle;
  
  // Clears the countdown timer when the player wins
  FTimerHandle WinMenuTimerHandle;
  
  // Clears the countdown timer when thep player runs out of time
  FTimerHandle LossMenuTimerHandle;
  
  // Sound effect played during a loss
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
  class USoundCue* LossSound;
  
  // Sound effect played during a win
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
  class USoundCue* WinSound;
	
};
