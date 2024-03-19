
#include "AbilitySystem/Task/BTS_TickAbilityTask.h"

UBTS_TickAbilityTask::UBTS_TickAbilityTask(const FObjectInitializer& ObjectInitializer)
{
	bTickingTask = true;
}

UBTS_TickAbilityTask* UBTS_TickAbilityTask::AbilityTaskOnTick(UGameplayAbility* OwningAbility, FName TaskInstanceName)
{
	UBTS_TickAbilityTask* MyObj = NewAbilityTask<UBTS_TickAbilityTask>(OwningAbility, TaskInstanceName);
	return MyObj;
}

void UBTS_TickAbilityTask::Activate()
{
	Super::Activate();
}

void UBTS_TickAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTick.Broadcast(DeltaTime);
	}
}
