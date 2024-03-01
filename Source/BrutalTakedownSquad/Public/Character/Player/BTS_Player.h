
#pragma once

#include "CoreMinimal.h"
#include "Character/BTS_CharacterBase.h"
#include "BTS_Player.generated.h"

// Player Base Class
// 
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Player : public ABTS_CharacterBase
{
	GENERATED_BODY()

public:
	ABTS_Player();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual float GetTurnRate() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
	void ChangePerspective();

protected:
	virtual void InitAbilityActorInfo() override;
};
