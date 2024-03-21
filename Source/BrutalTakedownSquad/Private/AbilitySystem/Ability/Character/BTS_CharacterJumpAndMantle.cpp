
#include "AbilitySystem/Ability/Character/BTS_CharacterJumpAndMantle.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Player/BTS_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/CurveTable.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"

#include "Abilities/Tasks/AbilityTask_WaitDelay.h"

void UBTS_CharacterJumpAndMantle::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	Character = Cast<ABTS_Player>(ActorInfo->AvatarActor.Get());
}

void UBTS_CharacterJumpAndMantle::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	Character = nullptr;

	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterJumpAndMantle::OnRemoveAbility"));
}

void UBTS_CharacterJumpAndMantle::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterJumpAndMantle::ActivateAbility"));

	//Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(OwnerInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, OwnerInfo, ActivationInfo))
		{
			return;
		}

		if (Character)
		{
			Character->Execute_SetIsAimable(Character, false);

			MantleTrace();

			// print MANTLE TYPE to UE_LOG
			switch (MantleType)
			{
				case EMantleType::None:
				UE_LOG(LogTemp, Warning, TEXT("MantleType : None"));
				break;
				case EMantleType::Mantle1M:
					UE_LOG(LogTemp, Warning, TEXT("MantleType : Mantle1M"));
					break;
					case EMantleType::Mantle2M:
						UE_LOG(LogTemp, Warning, TEXT("MantleType : Mantle2M"));
						break;
			}

			if (MantleType != EMantleType::None)
				Mantle(100);
			else
			{
				Character->Jump();

				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([this]()
				{
					EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
				});

				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);
			}
		}
	}
}

bool UBTS_CharacterJumpAndMantle::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (Character && Character->bIsCrouched)
	{
		Character->UnCrouch();

		return false;
	}

	if (Character && Character->GetVelocity().Z != 0 && Character->GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	return true;
}

void UBTS_CharacterJumpAndMantle::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UBTS_CharacterJumpAndMantle::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));
		return;
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (Character)
	{
		Character->StopJumping();
	}
}

void UBTS_CharacterJumpAndMantle::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UE_LOG(LogTemp, Warning, TEXT("UBTS_CharacterJumpAndMantle::EndAbility"));

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (Character)
	{
		Character->Execute_SetIsAimable(Character, true);
		
		if (MantleType != EMantleType::None)
		{
			Character->SetActorEnableCollision(true);
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			Character->bUseControllerRotationYaw = true;

			MantleType = EMantleType::None;
		}
	}
}

bool UBTS_CharacterJumpAndMantle::CommitAbilityCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	if (Super::CommitAbilityCost(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
		return true;

	UE_LOG(LogTemp, Warning, TEXT("End by cost"));

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

	return false;
}

void UBTS_CharacterJumpAndMantle::MantleTrace()
{
	FVector Start = Character->GetActorLocation(); Start.Z += 150;
	Start += Character->GetActorForwardVector() * 50;
	FVector End = Start; End.Z -= 200;

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Character);

	// check if there is a wall
	FHitResult CapsuleHitResult;
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 10 // radius : 10
		, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoredActors
		, EDrawDebugTrace::Persistent, CapsuleHitResult, true))
	{
		FVector HeadPos = Character->GetMesh()->GetSocketLocation("head");
		FVector calf = Character->GetMesh()->GetSocketLocation("calf_r");

		if (Start.Z - CapsuleHitResult.Location.Z < 0.001)
		{
			MantleType = EMantleType::None;
			return;
		}

		if (CapsuleHitResult.Location.Z > HeadPos.Z)
		{
			MantleType = EMantleType::Mantle2M;
			CurveTable = MantleCurveTable2M;
		}
		else if (CapsuleHitResult.Location.Z > calf.Z)
		{
			MantleType = EMantleType::Mantle1M;
			CurveTable = MantleCurveTable1M;
		}
		else
		{
			MantleType = EMantleType::None;
			return;
		}

		FRealCurve* RichCurve = CurveTable->FindCurveUnchecked("DirOffset");

		MantlePos1 = CapsuleHitResult.ImpactPoint + (Character->GetActorForwardVector() * RichCurve->Eval(1));
		MantlePos2 = CapsuleHitResult.ImpactPoint + (Character->GetActorForwardVector() * RichCurve->Eval(2));
		MantlePos3 = CapsuleHitResult.ImpactPoint + (Character->GetActorForwardVector() * RichCurve->Eval(3));
		MantlePos4 = CapsuleHitResult.ImpactPoint + (Character->GetActorForwardVector() * RichCurve->Eval(4));
	}
	else
		MantleType = EMantleType::None;
}

void UBTS_CharacterJumpAndMantle::Mantle(float ZOffsetLanding)
{
	Character->SetActorEnableCollision(false);
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	Character->bUseControllerRotationYaw = false;

	FRealCurve* RichCurve = CurveTable->FindCurveUnchecked("PosOffset");

	// mantle
	FMotionWarpingTarget Target1;
	Target1.Name = "MantlePoint1";
	Target1.Location = MantlePos1 + FVector(0, 0, RichCurve->Eval(1));
	Target1.Rotation = Character->GetActorRotation();
	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target1);

	FMotionWarpingTarget Target2;
	Target2.Name = "MantlePoint2";
	Target2.Location = MantlePos2 + FVector(0, 0, RichCurve->Eval(2));
	Target2.Rotation = Character->GetActorRotation();
	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target2);

	FMotionWarpingTarget Target3;
	Target3.Name = "MantlePoint3";
	Target3.Location = MantlePos3 + FVector(0, 0, RichCurve->Eval(3));
	Target3.Rotation = Character->GetActorRotation();
	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target3);

	FMotionWarpingTarget Target4;
	Target4.Name = "MantlePoint4";
	Target4.Location = MantlePos4 + FVector(0, 0, RichCurve->Eval(4));
	Target4.Rotation = Character->GetActorRotation();
	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target4);

	// montage
	float PlayRate = 1.f; // The speed at which to play the montage
	FName StartSectionName; // The section to start playing from

	UAnimMontage* MantleMontage = MantleType == EMantleType::Mantle1M ? MantleMontage1M : MantleMontage2M;

	// Create a 'PlayMontageAndWait' function
	UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, EName::None, MantleMontage, PlayRate, StartSectionName);

	PlayMontageTask->OnCompleted.AddDynamic(this, &UBTS_CharacterJumpAndMantle::EndJumpAndMantle);
	//PlayMontageTask->OnBlendOut.AddDynamic(this, &UBTS_CharacterJumpAndMantle::EndJumpAndMantle);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &UBTS_CharacterJumpAndMantle::EndJumpAndMantle);
	PlayMontageTask->OnCancelled.AddDynamic(this, &UBTS_CharacterJumpAndMantle::EndJumpAndMantle);

	PlayMontageTask->Activate();
}

void UBTS_CharacterJumpAndMantle::EndJumpAndMantle()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

