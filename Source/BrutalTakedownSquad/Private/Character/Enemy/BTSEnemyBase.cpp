// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/BTSEnemyBase.h"
#include"AbilitySystemComponent.h"
#include"AbilitySystem/BTS_AbilitySystemComponent.h"
#include"AbilitySystem/BTS_AttributeSet.h"
#include"Character/Enemy/BTSAIController.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"BehaviorTree/BehaviorTree.h"
ABTSEnemyBase::ABTSEnemyBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBTS_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	PrimaryActorTick.bCanEverTick = true;
	AttributeSet = CreateDefaultSubobject<UBTS_AttributeSet>("AttributeSet");


}

void ABTSEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	
	BTSAIController = Cast<ABTSAIController>(NewController);

	BTSAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BTSAIController->RunBehaviorTree(BehaviorTree);


}

void ABTSEnemyBase::Tick(float Deltatime)
{
	Super::Tick(Deltatime);

	if (const UBTS_AttributeSet* BTSAS = Cast<UBTS_AttributeSet>(AttributeSet))
	{
		//Todo
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Cyan, FString::Printf(TEXT("EnemyHealth : %f"), BTSAS->GetHealth()));
		
		float CurrentHealthPercent =  BTSAS->GetHealth()/ BTSAS->GetMaxHealth();
		if (CurrentHealthPercent <= 0.5f&&!DoOnce)
		{
			DoOnce = true;
			Runaway = true;
		}
		if (CurrentHealthPercent <= 0.0f)
		{
			Destroy();

		}

	}

}

void ABTSEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	
	


}

void ABTSEnemyBase::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UBTS_AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();

}
