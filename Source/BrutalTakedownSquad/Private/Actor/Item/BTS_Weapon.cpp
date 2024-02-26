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
	InteractiveRegion->SetupAttachment(RootSceneComp);
}

void ABTS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_Weapon::OnPickUp(UAbilitySystemComponent* ASC)
{
	Super::OnPickUp(ASC);

	ASC->
}


void ABTS_Weapon::OnDrop(UAbilitySystemComponent* ASC)
{
	Super::OnDrop(ASC);
}

UMeshComponent* ABTS_Weapon::GetMesh()
{
	return Mesh;
}
