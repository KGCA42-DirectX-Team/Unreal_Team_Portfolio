
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/Character/BTS_CharacterGameplayAbility.h"
#include "BTS_PlayerChangePerspective.generated.h"

// Player Change Perspective ability.
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_PlayerChangePerspective : public UBTS_CharacterGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

};
