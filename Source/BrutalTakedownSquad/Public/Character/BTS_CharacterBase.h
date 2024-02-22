
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "BTS_CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

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
	UPROPERTY(EditAnywhere, Category = "Equiped Item")
	TObjectPtr<AActor> ItemInHands;

	UPROPERTY(EditAnywhere, Category = "Equiped Item")
	TObjectPtr<AActor> Helmet;

	UPROPERTY(EditAnywhere, Category = "Equiped Item")
	TObjectPtr<AActor> BodyArmor;

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
