// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BTS_PlayerHUD.h"
#include "UI/UserWidget/BTS_PlayerUserWidget.h"
#include "UI/WidgetController/BTS_OverlayWidgetController.h"

UBTS_OverlayWidgetController* ABTS_PlayerHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UBTS_OverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependenceies();

		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void ABTS_PlayerHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAttributeSet* AS, UAbilitySystemComponent* ASC)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitalized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitalized, please fill out BP_AuraHUD"));

	UUserWidget* Widget =  CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UBTS_PlayerUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, AS, ASC);
	UBTS_OverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}
