// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTS_ItemUI.generated.h"

class UStaticMeshComponent;
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

// 컴포넌트
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Sphere;

//변수
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true, Instanced))
	TObjectPtr<UBTS_ItemObject> ItemObject;
};
