
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BTS_QuestState.generated.h"

class UBTS_Quest;

// BTS_QuestState is Base class for all quest states
// YWS
UCLASS(BlueprintType, Blueprintable)
class BRUTALTAKEDOWNSQUAD_API UBTS_QuestState : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Enter();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Execute();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Exit();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBTS_Quest> Quest;

};
