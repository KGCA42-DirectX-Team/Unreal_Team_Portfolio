// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BTS_BTTask_GetRandomLocation.h"
#include "Character/Enemy/BTSAIController.h"
#include"BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
EBTNodeResult::Type UBTS_BTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory); 
}
