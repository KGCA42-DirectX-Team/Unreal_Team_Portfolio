// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BTSCharacterBase.h"
#include "BTSEnemyBase.generated.h"


class UBehaviorTree;
class ABTSAIController;

// AI Enemy Base Class
// Admin: CHB
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSEnemyBase : public ABTSCharacterBase
{
	GENERATED_BODY()
	
public:
	ABTSEnemyBase();

	virtual void PossessedBy(AController* NewController)override;

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;


	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ABTSAIController> BTSAIController;

};
