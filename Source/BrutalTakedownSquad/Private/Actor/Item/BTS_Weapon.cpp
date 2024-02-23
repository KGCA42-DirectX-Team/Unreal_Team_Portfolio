// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/BTS_Weapon.h"


ABTS_Weapon::ABTS_Weapon()
{
}

void ABTS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_Weapon::OnPickUpOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	Super::OnPickUpOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ItemOwner->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(PrimaryAbilityClass));
	ItemOwner->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(SecondaryAbilityClass));
}
