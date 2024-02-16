#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BTSAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

/// <summary>
/// AbilitySystemComponent를 상속받아서 기능을 추가한 컴포넌트
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/15
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	FEffectAssetTags EffectAssetTags;

public:
	void AbilityActorInfoSet();

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	void AbilityInputTagHold(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
