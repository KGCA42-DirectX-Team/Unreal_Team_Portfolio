#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "BTS_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UBTS_InputConfig;
class UBTS_AbilitySystemComponent;

struct FInputActionValue;

// Player Controller
// 
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABTS_PlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> BTSContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UBTS_InputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UBTS_AbilitySystemComponent> AbilitySystemComponent;

private:
	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);

	void AbilityInputTagReleased(FGameplayTag InputTag);

	void AbilityInputTagHold(FGameplayTag InputTag);

	UBTS_AbilitySystemComponent* GetBTS_AbilitySystemComponent();
};
