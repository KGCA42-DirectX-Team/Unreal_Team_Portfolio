
#pragma once

#include "CoreMinimal.h"
#include "Character/BTSCharacterBase.h"
#include "BTSPlayer.generated.h"

// Player Base Class
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSPlayer : public ABTSCharacterBase
{
	GENERATED_BODY()

public:
	ABTSPlayer();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
	void ChangePerspective();

protected:
	virtual void InitAbilityActorInfo() override;
};
