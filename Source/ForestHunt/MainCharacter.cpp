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
