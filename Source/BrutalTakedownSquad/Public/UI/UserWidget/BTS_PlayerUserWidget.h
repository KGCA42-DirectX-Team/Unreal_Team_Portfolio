// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BTS_PlayerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_PlayerUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void WidgetControllerSet();
};
