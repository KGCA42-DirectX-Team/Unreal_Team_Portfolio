#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "BTSInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FBTSInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/// <summary>
/// AbilitySystemComponent를 상속받아서 기능을 추가한 컴포넌트
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/15
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FBTSInputAction> AbilityInputActions;

public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
};
