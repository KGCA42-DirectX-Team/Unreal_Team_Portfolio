// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Line.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BRUTALTAKEDOWNSQUAD_API FLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D End;
	
};
