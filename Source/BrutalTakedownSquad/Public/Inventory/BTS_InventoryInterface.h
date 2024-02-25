// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Actor/Item/BTS_Item.h"
#include "BTS_InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBTS_InventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BRUTALTAKEDOWNSQUAD_API IBTS_InventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddToInventory(AActor* Item) = 0;
	virtual void RemoveFromInventory(AActor* Item) = 0;
	virtual void ClearInventory() = 0;
};
