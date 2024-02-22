
#include "Input/BTS_InputConfig.h"

const UInputAction* UBTS_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FBTS_InputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("No input action found for tag %s"), *InputTag.ToString());
	}

	return nullptr;
}
