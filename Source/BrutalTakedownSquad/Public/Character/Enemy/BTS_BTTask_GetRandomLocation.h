// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTS_BTTask_GetRandomLocation.generated.h"


/// <summary>
/// AI Controller 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 채해병
/// @date last change 2024/02/20
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_BTTask_GetRandomLocation : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
