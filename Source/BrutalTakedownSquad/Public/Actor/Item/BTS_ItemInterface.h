// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BTS_ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBTS_ItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class BRUTALTAKEDOWNSQUAD_API IBTS_ItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnPickUp(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;

	virtual void OnDrop() = 0;
	//virtual UMeshComponent* GetMesh() = 0;
	virtual FName GetItemName() = 0;

	// Weapon related
	//virtual FName GetWeaponHandgripSocket() { return FName(); };
	//virtual FName GetWeaponMuzzleSocket() { return FName(); };
	//virtual FName GetWeaponMagazineSocket() { return FName(); };
	//
	//// Armor related
	//virtual FName GetBodyArmorSocket() { return FName(); };
};
