// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTS_ItemUI.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UBTS_ItemObject;

// ItemUI Base Class.
// Admin: PSC
UCLASS(Blueprintable)
class BRUTALTAKEDOWNSQUAD_API ABTS_ItemUI : public AActor
{
	GENERATED_BODY()
	
public:	
	ABTS_ItemUI();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEV MADE")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEV MADE")
	USkeletalMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEV MADE")
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEV MADE", Meta = (ExposeOnSpawn = true, Instanced))
	TObjectPtr<UBTS_ItemObject> ItemObject;
};
