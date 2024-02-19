// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BTS_BTService_FindNearestPlayer.h"
#include "AIController.h"

void UBTS_BTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Black, *AIOwner->GetName());
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, *ActorOwner->GetName());

	APawn* OwningPawn = AIOwner->GetPawn();



}
