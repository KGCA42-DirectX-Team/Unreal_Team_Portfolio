// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/BTSPlayerState.h"

#include "AbilitySystem/BTSAbilitySystemComponent.h"
#include "AbilitySystem/BTSAttributeSet.h"
#include "Net/UnrealNetwork.h"

ABTSPlayerState::ABTSPlayerState()
{
	NetUpdateFrequency = 100.f; // 서버가 클라이언트 업데이트를 시도하는 빈도.

	AbilitySystemComponent = CreateDefaultSubobject<UBTSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UBTSAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ABTSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABTSPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

void ABTSPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}
