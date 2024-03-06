
#include "AbilitySystem/Ability/Character/BTS_CharacterSprint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/BTS_CharacterBase.h"

void UBTS_CharacterSprint::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	Character = Cast<ABTS_CharacterBase>(ActorInfo->AvatarActor.Get());
	if(Character)
		CharacterMovement = Character->GetCharacterMovement();
}

void UBTS_CharacterSprint::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	Character = nullptr;
	CharacterMovement = nullptr;
}

void UBTS_CharacterSprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(OwnerInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, OwnerInfo, ActivationInfo))
		{
			return;
		}

		// Sprint
		if (Character && CharacterMovement)
		{
			Character->Execute_SetIsSprint(Character, true);
			Character->Execute_SetIsAimable(Character, false);

			CharacterMovement->MaxWalkSpeed = 600.0f;
		}
	}
}

bool UBTS_CharacterSprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return (CharacterMovement && CharacterMovement->IsMovingOnGround() && !Character->bIsCrouched);
}

void UBTS_CharacterSprint::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UBTS_CharacterSprint::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UBTS_CharacterSprint::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));
		return;
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	// Reset sprint
	if (Character && CharacterMovement)
	{
		Character->Execute_SetIsSprint(Character, false);
		Character->Execute_SetIsAimable(Character, true);

		CharacterMovement->MaxWalkSpeed = 300.0f;
	}
}


