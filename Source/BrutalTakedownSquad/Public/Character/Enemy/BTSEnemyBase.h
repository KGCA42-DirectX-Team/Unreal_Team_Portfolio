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

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ABTSAIController> BTSAIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool Runaway;
	bool DoOnce = false;
};
