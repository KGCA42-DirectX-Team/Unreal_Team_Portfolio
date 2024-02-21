
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BTSGameplayAbility.generated.h"

// Gameplay Ability Base Class
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
};
