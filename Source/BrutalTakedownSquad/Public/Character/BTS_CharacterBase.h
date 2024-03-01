
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"

#include "BTS_CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UBTS_AbilitySystemComponent;

// Character base class that uses the AbilitySystemComponent for abilities and attributes
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_CharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABTS_CharacterBase();

	// Rule: Always cast to BTS_UAbilitySystemComponent after calling this function
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

	// ICombatInterface을(를) 통해 상속됨
	void Die() override;

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	// For ABP

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetIsSprint(bool bNewSprint) { bIsSprint = bNewSprint; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool GetIsSprint() const { return bIsSprint; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual float GetTurnRate();

	// Getters and Setters for EquipedItemMesh
	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	void SetInHandItemMesh(UMeshComponent* NewMesh) { InHandItemMesh = NewMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	UMeshComponent* GetInHandItemMesh() const { return InHandItemMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	void SetPrimaryWeaponMesh(UMeshComponent* NewMesh) { PrimaryWeaponMesh = NewMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	UMeshComponent* GetPrimaryWeaponMesh() const { return PrimaryWeaponMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	void SetSecondaryWeaponMesh(UMeshComponent* NewMesh) { SecondaryWeaponMesh = NewMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	UMeshComponent* GetSecondaryWeaponMesh() const { return SecondaryWeaponMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	void SetHelmetMesh(UMeshComponent* NewMesh) { HelmetMesh = NewMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	UMeshComponent* GetHelmetMesh() const { return HelmetMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	void SetBodyArmorMesh(UMeshComponent* NewMesh) { BodyArmorMesh = NewMesh; }

	UFUNCTION(BlueprintCallable, Category = "EquipedItem")
	UMeshComponent* GetBodyArmorMesh() const { return BodyArmorMesh; }

protected:

	// EquipedItemMesh

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipedItem")
	TObjectPtr<UMeshComponent> InHandItemMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipedItem")
	TObjectPtr<UMeshComponent> PrimaryWeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipedItem")
	TObjectPtr<UMeshComponent> SecondaryWeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipedItem")
	TObjectPtr<UMeshComponent> HelmetMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EquipedItem")
	TObjectPtr<UMeshComponent> BodyArmorMesh;


	// AbilitySystemComponent and AttributeSet

	UPROPERTY()
	TObjectPtr<UBTS_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> VitalAttribute;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass) const;

	void AddCharacterAbilities() const;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	bool bIsSprint = false;
};
