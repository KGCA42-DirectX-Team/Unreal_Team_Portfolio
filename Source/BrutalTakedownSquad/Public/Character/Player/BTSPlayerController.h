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

/// <summary>
/// 플레이어 컨트롤러 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/15
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
