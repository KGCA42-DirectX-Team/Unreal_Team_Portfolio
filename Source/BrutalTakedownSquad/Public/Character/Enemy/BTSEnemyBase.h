// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BTS_CharacterBase.h"
#include "BTSEnemyBase.generated.h"


class UBehaviorTree;
class ABTSAIController;

// AI Enemy Base Class
// Admin: CHB
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSEnemyBase : public ABTS_CharacterBase
{
	GENERATED_BODY()
	
public:
	ABTSEnemyBase();

	virtual void PossessedBy(AController* NewController)override;

	virtual EAnimationState GetAnimationState_Implementation() override { return AnimationState; }

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	bool IsDead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	EAnimationState AnimationState;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ABTSAIController> BTSAIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool Runaway;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool CanThrowableGranade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FVector ImpactNormal;

	bool DoOnce = false;
};
