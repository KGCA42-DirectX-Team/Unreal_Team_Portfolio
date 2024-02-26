
#include "BTS_GameplayTags.h"
#include "GameplayTagsManager.h"

FBTS_GameplayTags FBTS_GameplayTags::GameplayTags;

void FBTS_GameplayTags::InitializeNativeGameplayTags()
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


	GameplayTags.InputTag_G = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.G"),
		FString("default drop/throw key")
	);

	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.E"),
		FString("default pick up key")
	);


	// item tags
	GameplayTags.Item_Weapon_Primary = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Primary"),
		FString("Primary Weapon")
	);

	GameplayTags.Item_Weapon_Secondary = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Weapon.Secondary"),
		FString("Secondary Weapon")
	);

	GameplayTags.Item_Armor_Helmet = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.Helmet"),
		FString("Helmet")
	);

	GameplayTags.Item_Armor_BodyArmor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Item.Armor.BodyArmor"),
		FString("Body Armor")
	);
}
