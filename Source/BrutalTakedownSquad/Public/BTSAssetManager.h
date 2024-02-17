
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BTSAssetManager.generated.h"

/// <summary>
/// AssetManager for the BTS module.
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author À¯¿ø¼®
/// @date last change 2024/02/17
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UBTSAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
