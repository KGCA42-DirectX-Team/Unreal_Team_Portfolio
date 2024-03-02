
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	EAnimationState AnimationState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player")
	EOnLandState OnLandState;

public:
	ABTS_Player();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	// IAnimationEnumInterface
	virtual EAnimationState GetAnimationState_Implementation() override { return AnimationState; }

	virtual EOnLandState GetOnLandState_Implementation() override { return OnLandState; }

	virtual float GetTurnRate_Implementation() override;

	// 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
	void ChangePerspective();

	// engine override
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void InitAbilityActorInfo() override;

private:
	void CheckHitSurfaceWhileSlide();

};
