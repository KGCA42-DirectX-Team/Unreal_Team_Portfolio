
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BTS_Quest.generated.h"

class UBTS_QuestState;
class ABTS_CharacterBase;

// BTS_Quest is Quest class Containing all the quest states
// YWS
UCLASS(BlueprintType, Blueprintable)
class BRUTALTAKEDOWNSQUAD_API UBTS_Quest : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Execute();

	UFUNCTION(BlueprintCallable)
	void SetState(UBTS_QuestState* NewState);

	UFUNCTION(BlueprintCallable)
	void SetOwner(ABTS_CharacterBase* NewOwner);

	UFUNCTION(BlueprintCallable)
	void SetIsCompleted(bool bNewCompleted) { bIsCompleted = bNewCompleted; }

	UFUNCTION(BlueprintCallable)
	ABTS_CharacterBase* GetOwner() const;

	UFUNCTION(BlueprintCallable)
	FString GetQuestDescription() const { return QuestDescription; }

	UFUNCTION(BlueprintCallable)
	bool GetIsCompleted() const { return bIsCompleted; }

	UFUNCTION(BlueprintCallable)
	void SetQuestDescription(const FString& NewDescription) { QuestDescription = NewDescription; }
		
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBTS_QuestState> CurrentState;

	TObjectPtr<ABTS_CharacterBase> Owner;

	FString QuestDescription;

	bool bIsCompleted = false;
};
