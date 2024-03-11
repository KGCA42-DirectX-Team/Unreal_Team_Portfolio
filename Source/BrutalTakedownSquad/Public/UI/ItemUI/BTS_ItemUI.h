// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTS_ItemUI.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UBTS_ItemObject;

UCLASS(Blueprintable)
class BRUTALTAKEDOWNSQUAD_API ABTS_ItemUI : public AActor
{
	GENERATED_BODY()
	
public:	
	ABTS_ItemUI();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cpp")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cpp")
	USkeletalMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cpp")
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp", Meta = (ExposeOnSpawn = true, Instanced))
	TObjectPtr<UBTS_ItemObject> ItemObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cpp")
	FName ItemName;
};
