
#include "Quest/BTS_Quest.h"
#include "Quest/BTS_QuestState.h"

void UBTS_Quest::Execute_Implementation()
{
	if (CurrentState)
		CurrentState->Execute();
}

void UBTS_Quest::SetState(UBTS_QuestState* NewState)
{
	if (CurrentState)
	{
		CurrentState->Exit();
	}
	if (NewState)
	{
		CurrentState = NewState;
		CurrentState->Quest = this;

		CurrentState->Enter();
	}
}

void UBTS_Quest::SetOwner(ABTS_CharacterBase* NewOwner)
{
	Owner = NewOwner;
}

ABTS_CharacterBase* UBTS_Quest::GetOwner() const
{
	return Owner;
}
