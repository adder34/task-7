// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TASK6_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision Volume")
	class USphereComponent* CollisionVolume;

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void Equip(class ATask6Character* Char);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	bool bIsGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh")
		FString WeaponName;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex);
};
