
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimationEnumInterface.generated.h"

UENUM(BlueprintType)
enum class EAnimationState : uint8
{
	None UMETA(DisplayName = "None"),
	Unarmed UMETA(DisplayName = "Unarmed"),
	Pistol UMETA(DisplayName = "Pistol"),
	Rifle UMETA(DisplayName = "Rifle")
};

UENUM(BlueprintType)
enum class EOnLandState : uint8
{
	None UMETA(DisplayName = "None"),
	NormalLand UMETA(DisplayName = "NormalLand"),
	SoftLand UMETA(DisplayName = "SoftLand"),
	HardLand UMETA(DisplayName = "HardLand")
};

// Interface for Animation Blueprint
// Admin: YWS
UINTERFACE(MinimalAPI, BlueprintType)
class UAnimationEnumInterface : public UInterface
{
	GENERATED_BODY()
};

class BRUTALTAKEDOWNSQUAD_API IAnimationEnumInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EAnimationState GetAnimationState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EOnLandState GetOnLandState();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetTurnRate();
};
