
#include "BTS_AssetManager.h"
#include "BTS_GameplayTags.h"

UBTS_AssetManager& UBTS_AssetManager::Get()
{
	check(GEngine);

	UBTS_AssetManager* BSTAssetManager = Cast<UBTS_AssetManager>(GEngine->AssetManager);

	return *BSTAssetManager;
}

void UBTS_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FBTS_GameplayTags::InitializeNativeGameplayTags();
}
