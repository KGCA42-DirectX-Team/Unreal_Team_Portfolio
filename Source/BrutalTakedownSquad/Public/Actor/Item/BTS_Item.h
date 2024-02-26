// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTS_ItemInterface.h"
#include "BTS_Item.generated.h"

class USphereComponent;
class UGameplayAbility;
struct FGameplayTag;

// item Base Class for all items including weapons and armors
// DOES NOT HAVE MESH
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

	virtual void WhenPickUpThisItem(UAbilitySystemComponent* RawASC) override;
	
	virtual void WhenDropThisItem(UAbilitySystemComponent* RawASC) override;

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
	TSubclassOf<UGameplayAbility> SharedAbilityClass;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilitySystem")
	FGameplayTag ItemTypeTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPickableToPlayer = false;
};
