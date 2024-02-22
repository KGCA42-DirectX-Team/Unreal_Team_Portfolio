// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "AbilitySystem/Ability/BTS_GameplayAbility.h"
#include "Character/BTS_CharacterBase.h"
#include "AbilitySystemComponent.h"

#include "BTS_Item.generated.h"

// item Base Class
// Admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	ABTS_Item();

	virtual void Tick(float DeltaTime) override;

	virtual void OnPickUpOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<USphereComponent> CollisionVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<UBTS_GameplayAbility> CommonAbilityClass; // drop, throw ability

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<ABTS_CharacterBase> ItemOwner;
};
