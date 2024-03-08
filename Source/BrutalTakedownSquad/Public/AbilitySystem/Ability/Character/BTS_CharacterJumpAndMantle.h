
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/Character/BTS_CharacterGameplayAbility.h"
#include "BTS_CharacterJumpAndMantle.generated.h"

class ABTS_Player;
class UAnimMontage;
class UCurveTable;

UENUM(BlueprintType)
enum class EMantleType : uint8
{
	None UMETA(DisplayName = "None"),
	Mantle1M UMETA(DisplayName = "Mantle1M"),
	Mantle2M UMETA(DisplayName = "Mantle2M"),
};

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
	FVector MantlePos3;
	FVector MantlePos4;
	UCurveTable* CurveTable;

	EMantleType MantleType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> MantleMontage1M;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> MantleMontage2M;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveTable> MantleCurveTable1M;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveTable> MantleCurveTable2M;

private:
	void MantleTrace();
	
	void Mantle(float ZOffsetLanding);

	UFUNCTION()
	void EndJumpAndMantle();
};
