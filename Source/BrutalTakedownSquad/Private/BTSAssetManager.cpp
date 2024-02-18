
#include "BTSAssetManager.h"
#include "BTSGameplayTags.h"

UBTSAssetManager& UBTSAssetManager::Get()
{
	check(GEngine);

	UBTSAssetManager* BSTAssetManager = Cast<UBTSAssetManager>(GEngine->AssetManager);

	return *BSTAssetManager;
}

void UBTSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FBTSGameplayTags::InitializeNativeGameplayTags();
}
