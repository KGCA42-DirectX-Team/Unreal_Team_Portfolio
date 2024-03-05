// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/BTS_PlayerWidgetController.h"

void UBTS_PlayerWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AttributeSet = WCParams.AttributeSet;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
}
