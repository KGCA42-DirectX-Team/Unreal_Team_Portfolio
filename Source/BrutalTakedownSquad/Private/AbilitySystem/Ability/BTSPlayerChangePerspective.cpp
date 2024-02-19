
#include "AbilitySystem/Ability/BTSPlayerChangePerspective.h"
#include "Character/Player/BTSPlayer.h"

void UBTSPlayerChangePerspective::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(OwnerInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, OwnerInfo, ActivationInfo))
		{
			return;
		}

		// Sprint
		ABTSPlayer* Character = Cast<ABTSPlayer>(OwnerInfo->AvatarActor.Get());

		if (Character)
		{
			Character->ChangePerspective();
		}

		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

bool UBTSPlayerChangePerspective::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}
