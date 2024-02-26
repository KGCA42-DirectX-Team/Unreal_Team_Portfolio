// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/BTS_Item.h"
#include "BTS_Weapon.generated.h"

class UGameplayAbility;

// Weapon Base Class
// Admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Weapon : public ABTS_Item
{
	GENERATED_BODY()

public:
	ABTS_Weapon();

	virtual void Tick(float DeltaTime) override;

	virtual void WhenPickUpThisItem(UAbilitySystemComponent* RawASC) override;

	virtual void WhenDropThisItem(UAbilitySystemComponent* RawASC) override;

	virtual UMeshComponent* GetMesh() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbilitySystem")
	TSubclassOf<UGameplayAbility> PrimaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbilitySystem")
	TSubclassOf<UGameplayAbility> SecondaryAbilityClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;
};
