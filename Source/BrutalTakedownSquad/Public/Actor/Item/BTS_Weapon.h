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

	virtual void OnPickUp(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnDrop() override;

	//virtual UMeshComponent* GetMesh() override;

	virtual FName GetItemName() override;

	//virtual FName GetWeaponHandgripSocket() override;

	//virtual FName GetWeaponMuzzleSocket() override;

	//virtual FName GetWeaponMagazineSocket() override;

	//=================================================================================================
	// 플레이어에게 전달되는 무기의 기본 공격
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<UBTS_GameplayAbility> PrimaryAbilityClass;

	// 플레이어에게 전달되는 무기의 보조 능력 (ADS)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<UBTS_GameplayAbility> SecondaryAbilityClass;
	//=================================================================================================

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
};
