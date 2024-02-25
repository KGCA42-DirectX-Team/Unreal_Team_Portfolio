#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BTS_AbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

// Feature expaneded AbilitySystemComponent
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	FEffectAssetTags EffectAssetTags;

public:
	void AbilityActorInfoSet();
	// Always use this to add a ability to the character
	void AddCharacterAbility(TSubclassOf<UGameplayAbility> Ability);

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	void AbilityInputTagHold(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
