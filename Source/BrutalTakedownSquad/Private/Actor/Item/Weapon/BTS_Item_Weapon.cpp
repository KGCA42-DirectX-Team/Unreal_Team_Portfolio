// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/BTS_Item_Weapon.h"
#include "Components/SphereComponent.h"
#include "Character/BTS_CharacterBase.h"
#include "AbilitySystemComponent.h"

ABTS_Item_Weapon::ABTS_Item_Weapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABTS_Item_Weapon::BeginPlay()
{
	Super::BeginPlay();

	auto Collider = FindComponentByClass<USphereComponent>();
	if (Collider)
	{
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ABTS_Item_Weapon::OnPickUpOverlap);
	}
}

void ABTS_Item_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABTS_Item_Weapon::OnPickUpOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ABTS_CharacterBase* Player = Cast<ABTS_CharacterBase>(OtherActor);
	if (!Player) return;

	if(!Player->HasAuthority()) return;

	Player->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(PrimaryAbilityClass));
	Player->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SecondaryAbilityClass));
}
