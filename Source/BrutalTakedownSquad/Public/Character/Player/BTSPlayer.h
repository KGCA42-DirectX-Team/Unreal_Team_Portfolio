
#pragma once

#include "CoreMinimal.h"
#include "Character/BTSCharacterBase.h"
#include "BTSPlayer.generated.h"

/// <summary>
/// BTS 플레이어 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/15
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSPlayer : public ABTSCharacterBase
{
	GENERATED_BODY()

public:
	ABTSPlayer();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

protected:
	virtual void InitAbilityActorInfo() override;
};
