
#include "AbilitySystem/Ability/Character/BTS_CharacterADS.h"
#include "Character/Player/BTS_Player.h"

void UBTS_CharacterADS::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	//Weapon = Cast<ABTS_Player>(ActorInfo->AvatarActor.Get())->GetPlayerWeapon();
}

void UBTS_CharacterADS::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	Weapon = nullptr;
}

void UBTS_CharacterADS::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterADS::ActivateAbility"));

	if (Weapon)
	{
		//Weapon->ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);
	}
}

bool UBTS_CharacterADS::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	//return Weapon && Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UBTS_CharacterADS::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterADS::InputReleased"));

	if (Weapon)
	{
		//Weapon->InputReleased(Handle, ActorInfo, ActivationInfo);
	}

	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UBTS_CharacterADS::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (Weapon)
	{
		//Weapon->CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	}

}
