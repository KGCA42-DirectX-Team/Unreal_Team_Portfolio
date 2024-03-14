// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BTS_WeaponComponent.h"

// Sets default values for this component's properties
UBTS_WeaponComponent::UBTS_WeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBTS_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBTS_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USkeletalMeshComponent* UBTS_WeaponComponent::GetWeaopnMeshComponent_Implementation()
{
	return nullptr;
}

void UBTS_WeaponComponent::Reload_Implementation()
{
}

void UBTS_WeaponComponent::RemoveMag_Implementation()
{
}

void UBTS_WeaponComponent::DrapMag_Implementation()
{
}

void UBTS_WeaponComponent::TakeMag_Implementation()
{
}

void UBTS_WeaponComponent::PlaceMag_Implementation()
{
}


