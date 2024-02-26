// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "BTS_ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
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
	UFUNCTION(BlueprintCallable)
	virtual void OnInsidePickUpDistance(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) {};

	UFUNCTION(BlueprintCallable)
	virtual void OnOutsidePickUpDistance(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) {};

	UFUNCTION(BlueprintCallable)
	// This function is called when the item is picked up
	virtual void WhenPickUpThisItem(UAbilitySystemComponent* RawASC) {};

	UFUNCTION(BlueprintCallable)
	// This function is called when the item is dropped
	virtual void WhenDropThisItem(UAbilitySystemComponent* RawASC) {};

	UFUNCTION(BlueprintCallable)
	// when character is whithin pick up distance
	virtual bool IsPickable() const { return false; }

	UFUNCTION(BlueprintCallable)
	// get item mesh. This is used to attach the item's mesh to the character
	virtual UMeshComponent* GetMesh() { return nullptr; }
};
