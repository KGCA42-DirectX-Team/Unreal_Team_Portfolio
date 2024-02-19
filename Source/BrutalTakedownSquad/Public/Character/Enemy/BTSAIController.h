// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BTSAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;


/// <summary>
/// AI Controller 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 채해병
/// @date last change 2024/02/19
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
