// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/BTS_Weapon.h"


ABTS_Weapon::ABTS_Weapon()
{
	ItemName = FName("Defualt weapon name");

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));
	SkeletalMesh->SetupAttachment(SphereCollider);
}

void ABTS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_Weapon::OnPickUp(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	Super::OnPickUp(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ItemOwnerCharacterBase->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(PrimaryAbilityClass));
	ItemOwnerCharacterBase->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SecondaryAbilityClass));
}

void ABTS_Weapon::OnDrop()
{
	Super::OnDrop();
}

//UMeshComponent* ABTS_Weapon::GetMesh()
//{
//	return SkeletalMesh;
//}

FName ABTS_Weapon::GetItemName()
{
	return ItemName;
}

//FName ABTS_Weapon::GetWeaponHandgripSocket()
//{
//	return FName();
//}
//
//FName ABTS_Weapon::GetWeaponMuzzleSocket()
//{
//	return FName();
//}
//
//FName ABTS_Weapon::GetWeaponMagazineSocket()
//{
//	return FName();
//}
