// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BTSEnemyBase.h"
#include"AbilitySystemComponent.h"
#include"AbilitySystem/BTSAbilitySystemComponent.h"
#include"AbilitySystem/BTSAttributeSet.h"
#include"Character/Enemy/BTSAIController.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTree.h"
ABTSEnemyBase::ABTSEnemyBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBTSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UBTSAttributeSet>("AttributeSet");


}

void ABTSEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	
	BTSAIController = Cast<ABTSAIController>(NewController);

	BTSAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BTSAIController->RunBehaviorTree(BehaviorTree);


}

void ABTSEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (const UBTSAttributeSet* BTSAS = Cast<UBTSAttributeSet>(AttributeSet))
	{
		//Todo

	}

}

void ABTSEnemyBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UBTSAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();

}
