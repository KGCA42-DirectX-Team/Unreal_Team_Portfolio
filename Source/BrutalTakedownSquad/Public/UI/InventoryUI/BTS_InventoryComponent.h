// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BTS_InventoryComponent.generated.h"

class UBTS_ItemObject;
struct FTile;

USTRUCT(BlueprintType)
struct FItemIndex
{
	GENERATED_BODY()

	UPROPERTY()
	bool Vaild;

	UPROPERTY()
	TObjectPtr<UBTS_ItemObject> ItemObject;
};

USTRUCT(BlueprintType)
struct FAmmo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RifleBullets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PistolBullets;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class BRUTALTAKEDOWNSQUAD_API UBTS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBTS_InventoryComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	TMap<UBTS_ItemObject*, FTile> GetAllItems();

	UFUNCTION(BlueprintCallable)
	void RemoveItem(UBTS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable)
	bool TryAddItem(UBTS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTile IndexToTile(int32 Index) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 TileToIndex(FTile Tile) const;

	UFUNCTION(BlueprintCallable)
	bool IsRoomAvailable(UBTS_ItemObject* ItemObject , int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable)
	void AddItemAt(UBTS_ItemObject* ItemObject, int32 TopLeftIndex);

	// ============ Getter and Setter for ammo============
	UFUNCTION(BlueprintCallable)
	int32 GetRifleAmmo() const { return Ammo.RifleBullets; }

	UFUNCTION(BlueprintCallable)
	void SetRifleAmmo(int32 Value) { Ammo.RifleBullets = Value; }

	UFUNCTION(BlueprintCallable)
	int32 GetPistolAmmo() const { return Ammo.PistolBullets; }

	UFUNCTION(BlueprintCallable)
	void SetPistolAmmo(int32 Value) { Ammo.PistolBullets = Value; }

	UFUNCTION(BlueprintCallable)
	void AddRifleAmmo(int32 Value) { Ammo.RifleBullets += Value; }

	UFUNCTION(BlueprintCallable)
	void AddPistolAmmo(int32 Value) { Ammo.PistolBullets += Value; }

	UFUNCTION(BlueprintCallable)
	void DecreaseRifleAmmo(int32 Value) { Ammo.RifleBullets -= Value; }

	UFUNCTION(BlueprintCallable)
	void DecreasePistolAmmo(int32 Value) { Ammo.PistolBullets -= Value; }
	
	//====================================================

protected:
	UFUNCTION(BlueprintCallable)
	FItemIndex GetItemIndex(int32 index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory")
	int32 Colums;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UBTS_ItemObject>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory")
	bool IsDirty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "Inventory")
	FAmmo Ammo;

	bool IsOnce = true;
};
