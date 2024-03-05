// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BTS_PlayerHUD.generated.h"

class UBTS_OverlayWidgetController;
class UBTS_PlayerUserWidget;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_PlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	UBTS_OverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAttributeSet* AS, UAbilitySystemComponent* ASC);
protected:


private:
	UPROPERTY()
	TObjectPtr<UBTS_PlayerUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBTS_PlayerUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UBTS_OverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBTS_OverlayWidgetController> OverlayWidgetControllerClass;
};
