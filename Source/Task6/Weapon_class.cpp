// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_class.h"

// Sets default values
AWeapon_class::AWeapon_class()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon_class::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon_class::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

