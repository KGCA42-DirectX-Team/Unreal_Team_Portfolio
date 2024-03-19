
#pragma once

#include "CoreMinimal.h"
#include "Character/BTS_CharacterBase.h"
#include "BTS_Player.generated.h"

class UMotionWarpingComponent;
class USpringArmComponent;
class UCameraComponent;

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

	UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }

	USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

	// IAnimationEnumInterface
	virtual EAnimationState GetAnimationState_Implementation() override { return AnimationState; }

	virtual EOnLandState GetOnLandState_Implementation() override { return OnLandState; }

	virtual float GetTurnRate_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
	void ChangePerspective();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
	void ShowDamageIndicator(FVector DamageLocation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
	void PlayerDie();

	virtual void BeginPlay() override;

	// engine override
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

private:
	void CheckHitSurfaceWhileSlide();

};
