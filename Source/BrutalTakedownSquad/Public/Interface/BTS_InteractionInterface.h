// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BTS_InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBTS_InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BRUTALTAKEDOWNSQUAD_API IBTS_InteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Visible();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interaction();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractionClear();
};
