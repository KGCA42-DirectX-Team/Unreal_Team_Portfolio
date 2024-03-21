// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/InteractionObject/BTS_C4Case.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include"UI/Interaction/BTS_InteractionProgress.h"
#include "Character/BTS_CharacterBase.h"
#include"UI/InventoryUI/BTS_InventoryComponent.h"
#include"UI/ItemUI/BTS_ItemObject.h"

ABTS_C4Case::ABTS_C4Case()
{
	ProgressBar = CreateDefaultSubobject<UWidgetComponent>("ProgressBar");
	ProgressBar->SetupAttachment(ItemMesh);
}

void ABTS_C4Case::Visible_Implementation()
{
	ItemMesh->SetRenderCustomDepth(true);

}

void ABTS_C4Case::Interaction_Implementation()
{
	GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			ABTS_CharacterBase* PC = Cast<ABTS_CharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
			PC->GetInventoryComponent()->TryAddItem(ItemObject);
			Destroy();
		}), ClearTimer, false);

	ProgressBar->SetVisibility(true);
	


}

void ABTS_C4Case::InteractionClear_Implementation()
{
	GetWorldTimerManager().PauseTimer(TimerHandle);
	ProgressBar->SetVisibility(false);
	ItemMesh->SetRenderCustomDepth(false);
}

void ABTS_C4Case::BeginPlay()
{
	Super::BeginPlay();

	ProgressWidget = Cast<UBTS_InteractionProgress>(ProgressBar->GetUserWidgetObject());

}

void ABTS_C4Case::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProgressBar->IsVisible())
	{
		float ElapesdTime = GetWorldTimerManager().GetTimerElapsed(TimerHandle);

		float Percent = ElapesdTime / ClearTimer;
		ProgressWidget->SetPercent(Percent);
	}
}
