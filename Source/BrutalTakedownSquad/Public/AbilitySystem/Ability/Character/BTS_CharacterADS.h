
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/Character/BTS_CharacterGameplayAbility.h"
#include "BTS_CharacterADS.generated.h"

class ABTS_Player;

// Character ADS Ability
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_CharacterADS : public UBTS_CharacterGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TObjectPtr<ABTS_Player> Player;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Character ADS")
	void ReleaseADS();
};
