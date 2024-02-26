// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTS_BTTask_Base.h"
#include "BTS_BTTask_FindPlaceToHide.generated.h"

/**
 * 
 */
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_BTTask_FindPlaceToHide : public UBTS_BTTask_Base
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBlackboardKeySelector HideLocation;
};
