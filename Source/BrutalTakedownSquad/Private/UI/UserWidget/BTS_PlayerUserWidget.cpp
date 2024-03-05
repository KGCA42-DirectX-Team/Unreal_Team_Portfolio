// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UserWidget/BTS_PlayerUserWidget.h"

void UBTS_PlayerUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
