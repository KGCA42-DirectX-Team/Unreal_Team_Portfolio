// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTS_BTService_SetSprint.generated.h"

/**
 * 
 */
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_BTService_SetSprint : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool IsSprint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WalkSpeed;

};
