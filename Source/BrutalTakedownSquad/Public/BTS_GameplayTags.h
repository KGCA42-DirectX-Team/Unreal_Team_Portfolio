
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

// Registered GameplayTags
// Admim: KSW
struct FBTS_GameplayTags
{
public:
	static const FBTS_GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	// primary
	FGameplayTag Attributes_MaxHealth;
	FGameplayTag Attributes_MaxStamina;
	
	// vital
	FGameplayTag Attributes_CurrentHealth;
	FGameplayTag Attributes_CurrentStamina;

	// meta tags
	FGameplayTag Damage;

	// effects tags
	FGameplayTag Effects_HitReact;

	// Input Tags
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Shift;
	FGameplayTag InputTag_Space;
	FGameplayTag InputTag_C;
	FGameplayTag InputTag_B;
	FGameplayTag InputTag_R;

	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag InputTag_G;
	FGameplayTag InputTag_E;

	// item tags
	FGameplayTag Item_Weapon_Primary;
	FGameplayTag Item_Weapon_Secondary;
	FGameplayTag Item_Armor_Helmet;
	FGameplayTag Item_Armor_BodyArmor;

private:
	static FBTS_GameplayTags GameplayTags;
};