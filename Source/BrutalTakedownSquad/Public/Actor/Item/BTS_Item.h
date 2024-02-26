// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTS_ItemInterface.h"
#include "GameplayTagContainer.h"
#include "BTS_Item.generated.h"

class USphereComponent;
class UBTS_GameplayAbility;

// item Base Class for all items including weapons and armors. NO MESH
// Admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Item : public AActor, public IBTS_ItemInterface
{
	GENERATED_BODY()

public:
	ABTS_Item();

	virtual void Tick(float DeltaTime) override;

	virtual void OnInsidePickUpDistance(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnOutsidePickUpDistance(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	virtual void OnPickUp(UAbilitySystemComponent* ASC) override;
	
	virtual void OnDrop(UAbilitySystemComponent* ASC) override;

	virtual bool IsPickable() const override { return bIsPickableToPlayer; }

	UFUNCTION(BlueprintCallable)
	void SetItemTypeTag(FGameplayTag NewTag);

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetItemTypeTag() const { return ItemTypeTag; }

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> InteractiveRegion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbilitySystem")
	TSubclassOf<UBTS_GameplayAbility> SharedAbilityClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilitySystem")
	FGameplayTag ItemTypeTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPickableToPlayer = false;
};
