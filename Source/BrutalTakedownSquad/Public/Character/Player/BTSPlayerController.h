#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"

#include "BTSPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UBTSInputConfig;
class UBTSAbilitySystemComponent;

struct FInputActionValue;

// Player Controller
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABTSPlayerController();
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
	TObjectPtr<UBTSInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UBTSAbilitySystemComponent> BTSAbilitySystemComponent;

private:
	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);

	void AbilityInputTagReleased(FGameplayTag InputTag);

	void AbilityInputTagHold(FGameplayTag InputTag);

	UBTSAbilitySystemComponent* GetASC();
};
