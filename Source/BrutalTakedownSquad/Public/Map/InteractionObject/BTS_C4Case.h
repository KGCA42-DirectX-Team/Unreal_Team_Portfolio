// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ItemUI/BTS_ItemUI.h"
#include "../../Interface/BTS_InteractionInterface.h"
#include "BTS_C4Case.generated.h"

class UBTS_InteractionProgress;
class UBTS_ItemObject;
class UWidgetComponent;

UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_C4Case : public ABTS_ItemUI ,public IBTS_InteractionInterface
{
	GENERATED_BODY()
	
public:

	ABTS_C4Case();

	virtual void Visible_Implementation() override;

	virtual void Interaction_Implementation() override;

	virtual void InteractionClear_Implementation() override;
protected:
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)

	TObjectPtr<UWidgetComponent> ProgressBar;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBTS_InteractionProgress> ProgressWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USoundBase> TimeSound;

	UPROPERTY(BlueprintReadOnly)
	bool WidgetVisible = true;

	UPROPERTY(BlueprintReadOnly)
	float ClearTimer = 4.0f;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle TimerHandle;

};
