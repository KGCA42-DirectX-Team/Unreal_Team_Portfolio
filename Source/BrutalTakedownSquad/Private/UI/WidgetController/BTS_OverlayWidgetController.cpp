// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/WidgetController/BTS_OverlayWidgetController.h"
#include "AbilitySystem/BTS_AttributeSet.h"

void UBTS_OverlayWidgetController::BroadcastInitialValues()
{
	const UBTS_AttributeSet* PlayerAttributeSet = CastChecked<UBTS_AttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(PlayerAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(PlayerAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(PlayerAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(PlayerAttributeSet->GetMaxStamina());
	OnAmmo_5mmChanged.Broadcast(PlayerAttributeSet->GetAmmo_5mm());
}

void UBTS_OverlayWidgetController::BindCallbacksToDependenceies()
{
	const UBTS_AttributeSet* PlayerAttributeSet = CastChecked<UBTS_AttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PlayerAttributeSet->GetHealthAttribute()).AddUObject(this, &UBTS_OverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PlayerAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UBTS_OverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PlayerAttributeSet->GetStaminaAttribute()).AddUObject(this, &UBTS_OverlayWidgetController::StaminaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PlayerAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UBTS_OverlayWidgetController::MaxStaminaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		PlayerAttributeSet->GetAmmo_5mmAttribute()).AddUObject(this, &UBTS_OverlayWidgetController::Ammo_5mmChanged);
}

void UBTS_OverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UBTS_OverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UBTS_OverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UBTS_OverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}

void UBTS_OverlayWidgetController::Ammo_5mmChanged(const FOnAttributeChangeData& Data) const
{
	OnAmmo_5mmChanged.Broadcast(Data.NewValue);
}
