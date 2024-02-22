
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BTS_AssetManager.generated.h"

UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_AssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UBTS_AssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
