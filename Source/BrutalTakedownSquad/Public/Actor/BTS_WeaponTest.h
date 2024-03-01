// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "BTS_WeaponTest.generated.h"

class ABTS_Player;
class ABTS_Projectile;

/**
 * 
 */
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_WeaponTest : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<ABTS_Projectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UBTS_WeaponTest();

	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//void AttachWeapon(ABTS_Player* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

protected:
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	ABTS_Player* Character;
};
