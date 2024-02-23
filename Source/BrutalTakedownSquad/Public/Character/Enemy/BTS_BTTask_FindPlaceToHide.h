// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTS_BTTask_FindPlaceToHide.generated.h"

/**
 * 
 */
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_BTTask_FindPlaceToHide : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBlackboardKeySelector HideLocation;
};
