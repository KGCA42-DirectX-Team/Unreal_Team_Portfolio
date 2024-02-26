
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BTS_PlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UBTS_AbilitySystemComponent;

// Player State
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABTS_PlayerState();

	// Rule: Always cast to BTS_UAbilitySystemComponent after calling this function
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBTS_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
