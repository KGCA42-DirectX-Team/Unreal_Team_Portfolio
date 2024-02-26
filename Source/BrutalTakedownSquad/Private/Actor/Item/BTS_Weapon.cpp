// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/BTS_Weapon.h"

ABTS_Weapon::ABTS_Weapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetSimulatePhysics(true);
	SetRootComponent(Mesh);

	RootSceneComp->SetupAttachment(Mesh);
	//InteractiveRegion->SetupAttachment(RootSceneComp);
}

void ABTS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_Weapon::WhenPickUpThisItem(UAbilitySystemComponent* RawASC)
{
	Super::WhenPickUpThisItem(RawASC);
 	UBTS_AbilitySystemComponent* ASC = CastChecked<UBTS_AbilitySystemComponent>(RawASC);

	TArray<TSubclassOf<UGameplayAbility>> AbilityClasses;
	AbilityClasses.Add(PrimaryAbilityClass);
	AbilityClasses.Add(SecondaryAbilityClass);

	ASC->AddCharacterAbilities(AbilityClasses);
}


void ABTS_Weapon::WhenDropThisItem(UAbilitySystemComponent* RawASC)
{
	Super::WhenDropThisItem(RawASC);
}

UMeshComponent* ABTS_Weapon::GetMesh()
{
	return Mesh;
}
