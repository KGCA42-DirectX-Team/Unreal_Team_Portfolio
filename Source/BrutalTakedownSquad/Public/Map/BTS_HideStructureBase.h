// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTS_HideStructureBase.generated.h"

UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_HideStructureBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABTS_HideStructureBase();

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StructureMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
