
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/Character/BTS_CharacterGameplayAbility.h"
#include "BTS_CharacterJumpAndMantle.generated.h"

class ABTS_Player;
class UAnimMontage;

// Character jump, Mantle ability.
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_CharacterJumpAndMantle : public UBTS_CharacterGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	TObjectPtr<ABTS_Player> Character;
	FVector MantlePos1;
	FVector MantlePos2;
	bool CanMantle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SlideMontage;

private:
	void MantleTrace(float InitialTraceLength, float SecondaryTraceZOffset, float FallingHeightMultiplier);
	
	void Mantle(float ZOffsetHand, float ZOffsetLanding, float ZOffsetLenght);

	UFUNCTION()
	void EndJumpAndMantle();
};
