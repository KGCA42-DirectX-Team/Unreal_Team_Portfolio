
#include "BTSGameplayTags.h"
#include "GameplayTagsManager.h"

FBTSGameplayTags FBTSGameplayTags::GameplayTags;

void FBTSGameplayTags::InitializeNativeGameplayTags()
{
	// Default Attribute Tags
	GameplayTags.Attributes_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxHealth"),
		FString("Maximum amount of Health obtainable")
	);

	GameplayTags.Attributes_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxStamina"),
		FString("Maximum amount of Stamina obtainable")
	);

	// Vital Attribute Tags
	GameplayTags.Attributes_CurrentHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.CurrentHealth"),
		FString("Current amount of Health")
	);

	GameplayTags.Attributes_CurrentStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.CurrentStamina"),
		FString("Current amount of Stamina")
	);

	// input tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
	);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
	);

	GameplayTags.InputTag_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Shift"),
		FString("Input Tag for Shift Key")
	);

	GameplayTags.InputTag_Space = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Space"),
		FString("Input Tag for Space Key")
	);

	GameplayTags.InputTag_C = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.C"),
		FString("Input Tag for C Key")
	);

	GameplayTags.InputTag_B = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.B"),
		FString("Input Tag for B Key")
	);



	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for Key1")
	);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for Key2")
	);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for Key3")
	);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for Key4")
	);
}
