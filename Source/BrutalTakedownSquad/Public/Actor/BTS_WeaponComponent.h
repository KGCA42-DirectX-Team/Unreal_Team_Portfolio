// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BTS_WeaponComponent.generated.h"

class UAnimMontage;
class USkeletalMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class BRUTALTAKEDOWNSQUAD_API UBTS_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UBTS_WeaponComponent();
	
	// For Animation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WeaponComponent")
	void Reload();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WeaponComponent")
	void RemoveMag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WeaponComponent")
	void DrapMag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WeaponComponent")
	void TakeMag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WeaponComponent")
	void PlaceMag();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WeaponComponent")
	USkeletalMeshComponent* GetWeaopnMeshComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> ReloadMontage;
		
};
