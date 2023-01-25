// Copyright Epic Games, Inc. All Rights Reserved.

#include "Task6Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon.h"
#include "Engine/SkeletalMeshSocket.h"



ATask6Character::ATask6Character()
{

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	
	TurnRateGamepad = 50.f;
	pick = false;
	Shoot = false;

	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 


	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 


}



void ATask6Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("FireGun", IE_Pressed, this, &ATask6Character::FireGun);

	PlayerInputComponent->BindAction("PickUpWeapon", IE_Pressed, this, &ATask6Character::pickUpWeapon);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ATask6Character::SwitchWeapon);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ATask6Character::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ATask6Character::MoveRight);


	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ATask6Character::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ATask6Character::LookUpAtRate);


	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATask6Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATask6Character::TouchStopped);
}

void ATask6Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ATask6Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ATask6Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ATask6Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ATask6Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATask6Character::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void ATask6Character::pickUpWeapon()
{
	pick = true;
}

void ATask6Character::SwitchWeapon() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Switch Weapon"));

	if (EquippedWeapon) {
		WeaponIndex = WeaponInventory.Find(EquippedWeapon);
		WeaponIndex += 1;
		if (WeaponIndex >= WeaponInventory.Num())
			WeaponIndex = 0;
		if (EquippedWeapon != WeaponInventory[WeaponIndex]) {
			EquippedWeapon->SetActorHiddenInGame(true);

			if (WeaponInventory[WeaponIndex]->bIsGun) {
				const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName("hand_rSocket_Gun");
				if (Socket) {
					Socket->AttachActor(WeaponInventory[WeaponIndex], GetMesh());
					SetEquippedWeapon(WeaponInventory[WeaponIndex]);
					EquippedWeapon->SetActorHiddenInGame(false);
					Cast<UMyAnimInstance>(this->GetMesh()->GetAnimInstance())->IsGun = true;
					Shoot = true;
				}
			}
			else
			{
				const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName("hand_rSocket_knife");
				if (Socket) {
					Socket->AttachActor(WeaponInventory[WeaponIndex], GetMesh());
					SetEquippedWeapon(WeaponInventory[WeaponIndex]);
					EquippedWeapon->SetActorHiddenInGame(false);
					Cast<UMyAnimInstance>(this->GetMesh()->GetAnimInstance())->IsGun = false;
					Shoot = false;
				}
			}
		}
	}
}


void ATask6Character::FireGun()
{
	if (Shoot == true) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("PEW PEW PEW"));
	}
	else
	{
		return;
	}

}
