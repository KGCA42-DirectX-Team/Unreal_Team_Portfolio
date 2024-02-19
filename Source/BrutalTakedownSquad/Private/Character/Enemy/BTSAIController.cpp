// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BTSAIController.h"
#include"BehaviorTree/BehaviorTreeComponent.h"
#include"BehaviorTree/BlackboardComponent.h"

ABTSAIController::ABTSAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComponent");
	check(Blackboard);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);

}
