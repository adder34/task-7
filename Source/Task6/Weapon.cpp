


#include "Weapon.h"
#include "Task6Character.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "MyAnimInstance.h"


AWeapon::AWeapon()
{	
	PrimaryActorTick.bCanEverTick = true;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Volume"));
	RootComponent = CollisionVolume;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	bIsGun = true;
}


void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnOverlapEnd);
}


void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::Equip(ATask6Character* Char) 
{

	if (Char)
	{
		if (bIsGun) 
		{
			const USkeletalMeshSocket* Socket = Char->GetMesh()->GetSocketByName("hand_rSocket_Gun");
			if (Socket) 
			{
				Socket->AttachActor(this, Char->GetMesh());

				Cast<UMyAnimInstance>(Char->GetMesh()->GetAnimInstance())->IsGun = true;

				Char->SetEquippedWeapon(this);
				Char->EquippedWeapon->SetActorHiddenInGame(false);
				Char->WeaponInventory.AddUnique(this);
			}
		}
		else
		{
			const USkeletalMeshSocket* Socket = Char->GetMesh()->GetSocketByName("hand_rSocket_Knife");
			if (Socket) 
			{
				Socket->AttachActor(this, Char->GetMesh());

				Cast<UMyAnimInstance>(Char->GetMesh()->GetAnimInstance())->IsGun = false;

				Char->SetEquippedWeapon(this);
				Char->EquippedWeapon->SetActorHiddenInGame(false);
				Char->WeaponInventory.AddUnique(this);
			}
		}
	}
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) 
	{
		ATask6Character* Char = Cast<ATask6Character>(OtherActor);
		if (Char) 
		{
			AWeapon* currentWeapon = Char->EquippedWeapon;
			if (currentWeapon) 
			{
				currentWeapon->SetActorHiddenInGame(true);
			}
			Equip(Char);
		}
	}
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex) 
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap ended"))
}
