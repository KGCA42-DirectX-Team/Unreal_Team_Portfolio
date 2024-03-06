
#include "AbilitySystem/Ability/Character/BTS_CharacterJumpAndMantle.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Player/BTS_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MotionWarpingComponent.h"
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
	Super::ActivateAbility(Handle, OwnerInfo, ActivationInfo, TriggerEventData);

	if (HasAuthorityOrPredictionKey(OwnerInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, OwnerInfo, ActivationInfo))
		{
			return;
		}

		if (Character)
		{
			Character->Execute_SetIsAimable(Character, false);

			MantleTrace(120, 200, 0.5f);

			if (CanMantle)
				Mantle(-100, 30, 1.f);
			else
				Character->Jump();
		}
	}
}

bool UBTS_CharacterJumpAndMantle::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	bool CanJump = Character && Character->CanJump();

	if (!CanJump && Character->bIsCrouched)
	{
		Character->UnCrouch();
	}

	return CanJump;
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
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (Character)
	{
		Character->Execute_SetIsAimable(Character, true);
		
		if (CanMantle)
		{
			Character->SetActorEnableCollision(true);
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			Character->bUseControllerRotationYaw = true;

			CanMantle = false;
		}
		Character->StopJumping();
	}
}

void UBTS_CharacterJumpAndMantle::MantleTrace(float InitialTraceLength, float SecondaryTraceZOffset, float FallingHeightMultiplier)
{
	CanMantle = true;

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
		FVector Temp = FVector( 0, 0, SecondaryTraceZOffset);
		Temp.Z = Character->GetMovementComponent()->IsFalling() ? Temp.Z * FallingHeightMultiplier : Temp.Z; // if player is falling, set reacheable height

		FVector MaxReachablePoint = CapsuleHitResult.Location + Temp;

		// check height of the wall
		FHitResult SphereHitResult;
		if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), MaxReachablePoint, CapsuleHitResult.Location, 10
			, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoredActors
			, EDrawDebugTrace::ForDuration, SphereHitResult, true))
		{
			MantlePos1 = SphereHitResult.ImpactPoint + (Character->GetActorForwardVector() * -50);
			MantlePos2 = SphereHitResult.ImpactPoint + (Character->GetActorForwardVector() * 120);

			// check there is enough space to mantle
			FVector MantleEnd = MantlePos2 + FVector(0, 0, 20);
			FHitResult MantleHitResult;
			if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), MantleEnd, MantleEnd, 10
				, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoredActors
				, EDrawDebugTrace::ForDuration, MantleHitResult, true))
			{
				CanMantle = false;
				return;
			}

			MantlePos2 = SphereHitResult.ImpactPoint + (Character->GetActorForwardVector() * 50);

			if (MantlePos1 == FVector::Zero() || MantlePos2 == FVector::Zero())
			{
				CanMantle = false;
				return;
			}
			// final check path between mantle pos1 and pos2 is clear
			FHitResult FinalHitResult;
			FVector FinalTraceStart = FVector(MantlePos1.X, MantlePos1.Y, MantlePos2.Z + 100);
			FVector FinalTraceEnd = MantlePos2 + FVector(0, 0, 100);

			if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), FinalTraceStart, FinalTraceEnd, 20
				, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, IgnoredActors
				, EDrawDebugTrace::ForDuration, FinalHitResult, true))
			{
				CanMantle = false;
				return;
			}
		}
	}
	else
	{
		CanMantle = false;
	}
}

void UBTS_CharacterJumpAndMantle::Mantle(float ZOffsetHand, float ZOffsetLanding, float ZOffsetLenght)
{
	Character->SetActorEnableCollision(false);
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	// MantlePoint1
	FMotionWarpingTarget Target1;
	Target1.Name = "MantlePoint1";
	Target1.Location = MantlePos1 + FVector(0, 0, ZOffsetHand); 
	Target1.Rotation = Character->GetActorRotation();
	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target1);

	// MantlePoint2
	FMotionWarpingTarget Target2;
	Target2.Name = "MantlePoint2";
	Target2.Location = MantlePos2 + FVector(0, 0, ZOffsetLanding);
	Target2.Rotation = Character->GetActorRotation();
	Character->GetMotionWarpingComponent()->AddOrUpdateWarpTarget(Target1);

	Character->bUseControllerRotationYaw = false;

	// need skeleton mesh
	Character->PlayAnimMontage(SlideMontage, 1.f, "Mantle");

	UAbilityTask_WaitDelay* WaitDelay = UAbilityTask_WaitDelay::WaitDelay(this, ZOffsetLenght);

	WaitDelay->OnFinish.AddDynamic(this, &UBTS_CharacterJumpAndMantle::EndJumpAndMantle);
	WaitDelay->Activate();
}

void UBTS_CharacterJumpAndMantle::EndJumpAndMantle()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
