
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
	float GetTurnRate() ;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsSprint() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsAimable() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsADS() const;

	// Setter
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetAnimationState(EAnimationState NewState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetOnLandState(EOnLandState NewState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTurnRate(float NewTurnRate);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsSprint(bool bNewSprint);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsAimable(bool bNewSprint);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetIsADS(bool bNewSprint);

};
