// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Task6Character.generated.h"



UCLASS(config=Game)
class ATask6Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ATask6Character();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
		class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
		TArray<AWeapon*> WeaponInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TArray<FString> WeaponList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	int WeaponIndex;

	bool Shoot;

	bool pick;

	void pickUpWeapon();

	void SwitchWeapon();

	void FireGun();

	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; };
	FORCEINLINE void SetEquippedWeapon(AWeapon* Weapon) { EquippedWeapon = Weapon; };

protected:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

