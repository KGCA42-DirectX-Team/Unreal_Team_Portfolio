
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "BTS_TickAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTickTaskDelegate, float, DeltaTime);

// Tick ability task.
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_TickAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UBTS_TickAbilityTask(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UBTS_TickAbilityTask* AbilityTaskOnTick(UGameplayAbility* OwningAbility, FName TaskInstanceName);

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	float TaskDeltaTime;

	UPROPERTY(BlueprintAssignable)
	FOnTickTaskDelegate OnTick;

};
