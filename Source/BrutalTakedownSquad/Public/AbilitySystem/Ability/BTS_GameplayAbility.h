
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BTS_GameplayAbility.generated.h"

// Gameplay Ability Base Class
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
};
