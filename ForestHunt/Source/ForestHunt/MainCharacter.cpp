// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  
  // Create Camera Boom (pulls towards the player if there's a collision)
  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(GetRootComponent());
  CameraBoom->TargetArmLength = 400.f; // Camera follows at this distance
  CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller
  
  // Set size for collision capsule
  GetCapsuleComponent()->SetCapsuleSize(34.f, 95.f);
  
  // Create Follow Camera
  FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
  FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
  // Attach the camera to the end of the boom and let the boom adjust to match
  // the controller orientation
  FollowCamera->bUsePawnControlRotation = false;
  
  // Don't rotate when the controller rotates
  // Let that only affect the camera
  bUseControllerRotationYaw = false;
  bUseControllerRotationPitch = false;
  bUseControllerRotationRoll = false;
  
  // Configure character movement
  GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
  GetCharacterMovement()->RotationRate = FRotator(0.0f, 840.f, 0.0f); // ...at this rotation rate
  GetCharacterMovement()->JumpZVelocity = 400.f;
  GetCharacterMovement()->AirControl = 0.5f; // Allow some control while airborne
  
  // Initialize total and collected items and the countdown
  TotalItems = 9;
  CollectedItems = 0;
  
  CountdownTime = 200;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
  
  // Set the countdown timer
  GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AMainCharacter::AdvanceTimer, 1.0f, true);
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
  check(PlayerInputComponent);
  
  PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
  PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
  
  PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &AMainCharacter::Quit);
  
  PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
  
  PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
  PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
  
}

// Forward/backward movement input
void AMainCharacter::MoveForward(float Value)
{
  if((Controller != nullptr) && (Value != 0.0f))
  {
    // Find out which way is forward
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(Direction, Value);
  }
}

// Right/left movement input
void AMainCharacter::MoveRight(float Value)
{
  if((Controller != nullptr) && (Value != 0.0f))
  {
    // Find out which way is forward
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
    
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
  }
}

// Increments the player's item count by one
void AMainCharacter::IncrementItems()
{
  // Increment the number of collected items
  CollectedItems++;
  // If you've collected all the items, you win!
  if(CollectedItems == TotalItems)
  {
    Win();
  }
}

// Advances the countdown timer by one
void AMainCharacter::AdvanceTimer()
{
  // Decrement the amount of remaining time
  --CountdownTime;
  // If remaining time is zero or less...
  if(CountdownTime < 1)
  {
    // Clear the timer
    GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
    // And you lose
    Lose();
  }
}

// Called when the player runs out of time
void AMainCharacter::Lose()
{
  UE_LOG(LogTemp, Warning, TEXT("Time's up!"));
  if(LossSound)
  {
    UGameplayStatics::PlaySound2D(this, LossSound);
  }
  // Disable player input
  this->DisableInput(GetWorld()->GetFirstPlayerController());
  // Set a timer to delay going back to the main menu
  GetWorldTimerManager().SetTimer(LossMenuTimerHandle, this, &AMainCharacter::ReturnToMainMenu, 1.0f, true, 2.0f);
}

// Called when the player collects every item
void AMainCharacter::Win()
{
  UE_LOG(LogTemp, Warning, TEXT("You win!"));
  if(WinSound)
  {
    UGameplayStatics::PlaySound2D(this, WinSound);
  }
  // Stop the countdown
  GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
  // Disable player input
  this->DisableInput(GetWorld()->GetFirstPlayerController());
  // Set a timer to delay going back to the main menu
  GetWorldTimerManager().SetTimer(WinMenuTimerHandle, this, &AMainCharacter::ReturnToMainMenu, 1.0f, true, 2.0f);
}

// Exit to the main menu mid-game
void AMainCharacter::Quit()
{
  UE_LOG(LogTemp, Warning, TEXT("Quitting game early"));
  GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
  ReturnToMainMenu();
}

// Return to the main menu
void AMainCharacter::ReturnToMainMenu()
{
  // Clear any win/loss timers for returning to the main menu
  if(GetWorldTimerManager().IsTimerActive(LossMenuTimerHandle))
  {
    GetWorldTimerManager().ClearTimer(LossMenuTimerHandle);
  }
  
  if(GetWorldTimerManager().IsTimerActive(WinMenuTimerHandle))
  {
    GetWorldTimerManager().ClearTimer(WinMenuTimerHandle);
  }
  UE_LOG(LogTemp, Warning, TEXT("Returning to main menu..."));
  // Open the Main Menu level
  UGameplayStatics::OpenLevel(this, "MainMenu");
}

