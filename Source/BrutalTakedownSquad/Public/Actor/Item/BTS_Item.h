// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BTS_ItemInterface.h"
#include "Components/SphereComponent.h"
#include "AbilitySystem/Ability/BTS_GameplayAbility.h"
#include "Character/BTS_CharacterBase.h"
#include "AbilitySystemComponent.h"

#include "BTS_Item.generated.h"

// item Base Class
// Admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Item : public AActor, public IBTS_ItemInterface
{
	GENERATED_BODY()

public:
	ABTS_Item();

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<ABTS_CharacterBase> ItemOwnerCharacterBase;

	//=================================================================================================
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<UBTS_GameplayAbility> SharedItemAbilityClass;
	//=================================================================================================

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
