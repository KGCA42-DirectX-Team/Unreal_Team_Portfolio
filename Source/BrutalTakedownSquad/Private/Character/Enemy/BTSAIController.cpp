// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BTSAIController.h"
#include"BehaviorTree/BehaviorTreeComponent.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"

ABTSAIController::ABTSAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComponent");
	check(Blackboard);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
}

void ABTSAIController::PerceptionUpdate(AActor* Actor, FAIStimulus stimulus)
{

	if (stimulus.WasSuccessfullySensed())
	{

		if (stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
		{
			GetWorldTimerManager().ClearTimer(EnemyTimer);

			Blackboard->SetValueAsObject(FName(TEXT("TargetActor")),Actor);
			Blackboard->SetValueAsBool(FName(TEXT("HasSight")), true);

		
		}
		if (stimulus.Type == UAISense::GetSenseID<UAISense_Hearing>())
		{

			Blackboard->SetValueAsVector(FName("TargetLocation"), stimulus.StimulusLocation);

		
		}


	}
	else
	{
		GetWorldTimerManager().SetTimer(EnemyTimer,this, &ABTSAIController::StartEnemyTimer, SightTime, false);
	}


}

void ABTSAIController::StartEnemyTimer()
{
	Blackboard->SetValueAsObject(FName(TEXT("TargetActor")), nullptr);
	Blackboard->SetValueAsBool(FName(TEXT("HasSight")), false);
}
