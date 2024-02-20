// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTS_BTService_FindNearestPlayer.generated.h"


/// <summary>
/// AI Controller 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 채해병
/// @date last change 2024/02/20
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_BTService_FindNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	

protected:


	virtual void TickNode(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory , float DeltaSeconds)override;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FBlackboardKeySelector TargetActorSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;

};
