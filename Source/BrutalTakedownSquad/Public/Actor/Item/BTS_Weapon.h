// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Item/BTS_Item.h"
#include "BTS_Weapon.generated.h"


// Weapon Base Class
// Admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Weapon : public ABTS_Item
{
	GENERATED_BODY()

public:
	ABTS_Weapon();

	virtual void Tick(float DeltaTime) override;

	virtual void OnPickUp(UAbilitySystemComponent* ASC) override;

	virtual void OnDrop(UAbilitySystemComponent* ASC) override;

	virtual UMeshComponent* GetMesh() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbilitySystem")
	TSubclassOf<UBTS_GameplayAbility> PrimaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbilitySystem")
	TSubclassOf<UBTS_GameplayAbility> SecondaryAbilityClass;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;
};
