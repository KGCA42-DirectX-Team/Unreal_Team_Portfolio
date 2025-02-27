// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BTSAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

struct FAIStimulus;
// AI Controller for the AI Characters
// Admin: CHB
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ABTSAIController();
	
	UFUNCTION(BlueprintCallable)
	void PerceptionUpdate(AActor* Actor , FAIStimulus stimulus);

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle EnemyTimer;

	UPROPERTY(EditAnywhere)
	float SightTime = 2.0f;

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;


private:
	

	void StartEnemyTimer();
	
};
