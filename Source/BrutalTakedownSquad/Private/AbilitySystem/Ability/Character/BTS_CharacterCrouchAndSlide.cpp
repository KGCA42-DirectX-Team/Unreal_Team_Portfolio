
#include "AbilitySystem/Ability/Character/BTS_CharacterCrouchAndSlide.h"

#include "Character/BTS_CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UBTS_CharacterCrouchAndSlide::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	Character = Cast<ABTS_CharacterBase>(ActorInfo->AvatarActor.Get());

	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterCrouchAndSlide::OnGiveAbility"));
}

void UBTS_CharacterCrouchAndSlide::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	Character = nullptr;
}

void UBTS_CharacterCrouchAndSlide::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(OwnerInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, OwnerInfo, ActivationInfo))
		{
			return;
		}

		// Slide	// temp code : if all character can slide, then we need to change this code.
		FVector2D Velocity = FVector2D(Character->GetVelocity().X, Character->GetVelocity().Y);
		float VelocityLength = Velocity.Length();

		if (VelocityLength > 500)
		{
			Character->GetCharacterMovement()->MaxWalkSpeedCrouched = 700.f;
			Character->Execute_SetIsAimable(Character,false);
			Character->Crouch();

			float PlayRate = 1.f; // The speed at which to play the montage
			FName StartSectionName; // The section to start playing from

			// Create a 'PlayMontageAndWait' function
			UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, EName::None, SlideMontage, PlayRate, StartSectionName);

			//PlayMontageTask->OnBlendOut.AddDynamic(this, &UBTS_CharacterCrouchAndSlide::EndSlide);
			PlayMontageTask->OnCompleted.AddDynamic(this, &UBTS_CharacterCrouchAndSlide::EndSlide);
			PlayMontageTask->OnInterrupted.AddDynamic(this, &UBTS_CharacterCrouchAndSlide::EndSlide);
			PlayMontageTask->OnCancelled.AddDynamic(this, &UBTS_CharacterCrouchAndSlide::EndSlide);

			PlayMontageTask->Activate();
		}
		else
		{
			if (Character->bIsCrouched)
				Character->UnCrouch();
			else
				Character->Crouch();

			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
	}
}

bool UBTS_CharacterCrouchAndSlide::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if(Character)
		return !Character->GetCharacterMovement()->IsFalling();

	return false;
}

void UBTS_CharacterCrouchAndSlide::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterCrouchAndSlide::CancelAbility"));

	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UBTS_CharacterCrouchAndSlide::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));

		return;
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UBTS_CharacterCrouchAndSlide::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterCrouchAndSlide::EndAbility"));

	Character->GetCharacterMovement()->MaxWalkSpeedCrouched = 200.f;
	Character->Execute_SetIsAimable(Character,true);

	if (Character->GetMesh()->GetAnimInstance()->Montage_IsPlaying(SlideMontage))	
	{
		// if we need do something when slide end, we can add code here.

		MontageStop(SlideMontage->BlendOut.GetBlendTime());
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBTS_CharacterCrouchAndSlide::EndSlide()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
