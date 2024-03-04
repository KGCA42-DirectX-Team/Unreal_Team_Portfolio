// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BTS_InventoryComponent.generated.h"

class UBTS_ItemObject;
struct FTile;

// InventoryComponent Base Class.
// Admin: PSC

USTRUCT(BlueprintType)
struct FItemIndex
{
	GENERATED_BODY()

	UPROPERTY()
	bool Vaild;

	UPROPERTY()
	TObjectPtr<UBTS_ItemObject> ItemObject;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class BRUTALTAKEDOWNSQUAD_API UBTS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBTS_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	TMap<UBTS_ItemObject*, FTile> GetAllItems();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTile IndexToTile(int32 Index) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 TileToIndex(FTile Tile) const;

	UFUNCTION(BlueprintCallable)
	void RemoveItem(UBTS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable)
	bool IsRoomAvailable(UBTS_ItemObject* ItemObject , int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable)
	void AddItemAt(UBTS_ItemObject* ItemObject, int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable)
	bool TryAddItem(UBTS_ItemObject* ItemObject);

protected:
	UFUNCTION(BlueprintCallable)
	FItemIndex GetItemIndex(int32 index);



protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 Colums;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UBTS_ItemObject>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	bool IsDirty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 Riflebullets;

	UPROPERTY()
	bool IsOnce = true;

};
