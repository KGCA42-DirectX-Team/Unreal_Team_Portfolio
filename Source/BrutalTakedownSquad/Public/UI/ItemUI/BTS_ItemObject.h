// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "BTS_ItemObject.generated.h"

class UMaterialInterface;
class ABTS_ItemUI;

UCLASS(Blueprintable)
class BRUTALTAKEDOWNSQUAD_API UBTS_ItemObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "cpp", BlueprintPure)
	FIntPoint GetDimensions() const;

	UFUNCTION(BlueprintCallable, Category = "cpp", BlueprintPure)
	UMaterialInterface* GetIcon() const;

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void Rotate();

	UFUNCTION(BlueprintCallable, Category = "cpp", BlueprintPure)
	bool IsRotate() const { return Rotated; }

	UFUNCTION(BlueprintCallable, Category = "cpp", BlueprintPure)
	FName GetItemID() const { return ItemID; }

	UFUNCTION(BlueprintCallable, Category = "cpp")
	void SetItemID(FName NewItemID) { ItemID = NewItemID; }

	UFUNCTION(BlueprintCallable, Category = "cpp", BlueprintPure)
	FGameplayTag GetItemTypeTag() const { return ItemTypeTag; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cpp")
	bool Rotated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp", Meta = (ExposeOnSpawn = true, Instanced))
	FIntPoint Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp", Meta = (ExposeOnSpawn = true, Instanced))
	TObjectPtr<UMaterialInterface> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp", Meta = (ExposeOnSpawn = true, Instanced))
	TObjectPtr<UMaterialInterface> IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp", Meta = (ExposeOnSpawn = true, Instanced))
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp", Meta = (ExposeOnSpawn = true, Instanced))
	FGameplayTag ItemTypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp", Meta = (ExposeOnSpawn = true, Instanced))
	TObjectPtr<UDataTable> ItemDataTable;
};
