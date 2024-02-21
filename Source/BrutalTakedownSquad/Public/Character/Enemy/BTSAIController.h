// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BTSAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;


// AI Controller for the AI Characters
// Admin: CHB
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ABTSAIController();
	

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;



private:

};
