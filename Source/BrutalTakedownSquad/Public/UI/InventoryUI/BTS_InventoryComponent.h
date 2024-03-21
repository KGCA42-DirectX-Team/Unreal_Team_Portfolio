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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp")
	bool Vaild;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp")
	TObjectPtr<UBTS_ItemObject> ItemObject;
};

USTRUCT(BlueprintType)
struct FAmmo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp")
	int32 RifleAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp")
	int32 ShotgunAmmo;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class BRUTALTAKEDOWNSQUAD_API UBTS_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBTS_InventoryComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "cpp")
	TMap<UBTS_ItemObject*, FTile> GetAllItems();

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void RemoveItem(UBTS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable, Category = "cpp")
	bool TryAddItem(UBTS_ItemObject* ItemObject);

	UFUNCTION(BlueprintCallable, Category = "cpp", BlueprintPure)
	FTile IndexToTile(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "cpp", BlueprintPure)
	int32 TileToIndex(FTile Tile) const;

	UFUNCTION(BlueprintCallable, Category = "cpp")
	bool IsRoomAvailable(UBTS_ItemObject* ItemObject, int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void AddItemAt(UBTS_ItemObject* ItemObject, int32 TopLeftIndex);

	// ============ Getter and Setter for ammo============
	UFUNCTION(BlueprintCallable, Category = "cpp")
	int32 GetRifleAmmo() const { return Ammo.RifleAmmo; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void SetRifleAmmo(int32 Value) { Ammo.RifleAmmo = Value; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	int32 GetPistolAmmo() const { return Ammo.ShotgunAmmo; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void SetPistolAmmo(int32 Value) { Ammo.ShotgunAmmo = Value; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void AddRifleAmmo(int32 Value) { Ammo.RifleAmmo += Value; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void AddPistolAmmo(int32 Value) { Ammo.ShotgunAmmo += Value; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void DecreaseRifleAmmo(int32 Value) { Ammo.RifleAmmo -= Value; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void DecreasePistolAmmo(int32 Value) { Ammo.ShotgunAmmo -= Value; }

	//====================================================

protected:
	UFUNCTION(BlueprintCallable, Category = "cpp")
	FItemIndex GetItemIndex(int32 index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "cpp")
	int32 Colums;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "cpp")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp")
	TArray<TObjectPtr<UBTS_ItemObject>> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cpp")
	TMap<TObjectPtr<UBTS_ItemObject>, int32> StoredItemCounts;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "cpp")
	bool IsDirty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "cpp")
	FAmmo Ammo;

private:
	bool IsOnce = true;
};
