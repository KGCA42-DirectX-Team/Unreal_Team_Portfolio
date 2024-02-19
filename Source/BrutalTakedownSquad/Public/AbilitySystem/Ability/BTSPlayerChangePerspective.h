
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/BTSGameplayAbility.h"
#include "BTSPlayerChangePerspective.generated.h"

/// <summary>
/// Player Change Perspective ability.
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author À¯¿ø¼®
/// @date last change 2024/02/19
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSPlayerChangePerspective : public UBTSGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

};
