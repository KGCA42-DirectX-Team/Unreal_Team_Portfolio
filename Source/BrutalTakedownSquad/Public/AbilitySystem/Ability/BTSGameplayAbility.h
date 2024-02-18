
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BTSGameplayAbility.generated.h"

/// <summary>
/// 베이스 게임플레이 어빌리티 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/15
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
};
