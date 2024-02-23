// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BTS_InventoryInterface.h"
#include "BTS_Inventory.generated.h"


// admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_Inventory : public UObject, public IBTS_InventoryInterface
{
	GENERATED_BODY()
	
public:
	UBTS_Inventory();

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<ABTS_Item>> StoredItems;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void AddToInventory(AActor* Item) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void RemoveFromInventory(AActor* Item) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void ClearInventory() override;
};
