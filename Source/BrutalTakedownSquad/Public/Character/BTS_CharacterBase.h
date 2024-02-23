
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BTS_CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class ABTS_Item;

// Character base class that uses the AbilitySystemComponent for abilities and attributes
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABTS_CharacterBase();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetIsSprint(bool bNewSprint) { bIsSprint = bNewSprint; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool GetIsSprint() const { return bIsSprint; }

protected:

	// =========================================================================
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equiped Item")
	TObjectPtr<ABTS_Item> ItemInHands;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equiped Weapon")
	TObjectPtr<ABTS_Item> PrimaryWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equiped Weapon")
	TObjectPtr<ABTS_Item> SecondaryWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equiped Armor")
	TObjectPtr<ABTS_Item> Helmet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equiped Armor")
	TObjectPtr<ABTS_Item> BodyArmor;

	//===========================================================================

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

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

	bool bIsSprint = false;
};
