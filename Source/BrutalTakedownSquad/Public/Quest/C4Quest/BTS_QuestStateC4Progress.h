
#pragma once

#include "CoreMinimal.h"
#include "Quest/BTS_QuestState.h"
#include "BTS_QuestStateC4Progress.generated.h"

// C4 Quest Progress State
// YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_QuestStateC4Progress : public UBTS_QuestState
{
	GENERATED_BODY()
	
	void Enter_Implementation() override;
	
	void Execute_Implementation() override;
	
	void Exit_Implementation() override;
};
