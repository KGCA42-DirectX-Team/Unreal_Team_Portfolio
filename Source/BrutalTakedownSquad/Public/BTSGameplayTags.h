
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/// <summary>
/// AbilitySystemComponent를 상속받아서 기능을 추가한 컴포넌트
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/18
struct FBTSGameplayTags
{
public:
	static const FBTSGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_MaxHealth;
	FGameplayTag Attributes_MaxStamina;
	FGameplayTag Attributes_CurrentHealth;
	FGameplayTag Attributes_CurrentStamina;

	// Input Tags
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Shift;
	FGameplayTag InputTag_Space;
	FGameplayTag InputTag_C;

	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

private:
	static FBTSGameplayTags GameplayTags;
};