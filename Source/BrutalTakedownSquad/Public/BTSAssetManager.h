
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BTSAssetManager.generated.h"

UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UBTSAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
