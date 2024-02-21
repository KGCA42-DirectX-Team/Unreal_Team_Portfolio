// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BTS_Item.generated.h"

// item Base Class
// Admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	ABTS_Item();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
