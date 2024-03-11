// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/InteractionObject/BTS_C4.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include"Character/BTS_CharacterBase.h"
#include"AbilitySystem/BTS_AbilitySystemComponent.h"
#include"UI/Interaction/BTS_InteractionProgress.h"
#include"Kismet/KismetSystemLibrary.h"
#include"BrutalTakedownSquad/Public/BTS_GameplayTags.h"
#include"AbilitySystemBlueprintLibrary.h"

// Sets default values
ABTS_C4::ABTS_C4()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	C4Mesh = CreateDefaultSubobject<UStaticMeshComponent>("C4Mesh");
	C4Mesh->SetupAttachment(RootComponent);
	TriggerLine = CreateDefaultSubobject<UStaticMeshComponent>("TriggerLine");
	TriggerLine->SetupAttachment(C4Mesh);
	Collision = CreateDefaultSubobject<USphereComponent>("SphereColiision");
	Collision->SetupAttachment(C4Mesh);
	Clearwidget = CreateDefaultSubobject<UWidgetComponent>("ClearWidget");
	Clearwidget->SetupAttachment(C4Mesh);
	ProgressBar = CreateDefaultSubobject<UWidgetComponent>("ProgressBar");
	ProgressBar->SetupAttachment(C4Mesh);


}

void ABTS_C4::Visible_Implementation()
{
	if (WidgetVisible)
	{
		FTimerHandle localTimerHandle;
		Clearwidget->SetVisibility(true);
		GetWorldTimerManager().SetTimer(localTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				Clearwidget->SetVisibility(false);
				GetWorld()->GetTimerManager().ClearTimer(localTimerHandle);
			}), 0.2f, false);

	}
}

void ABTS_C4::Interaction_Implementation()
{

	GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}), ClearTimer, false);

	ProgressBar->SetVisibility(true);
	WidgetVisible = false;

}

void ABTS_C4::InteractionClear_Implementation()
{
	GetWorldTimerManager().PauseTimer(TimerHandle);
	WidgetVisible = true;
	ProgressBar->SetVisibility(false);

}

void ABTS_C4::TriggerLineOverlap(AActor* OtherActor)
{
	int a = 0;
	OverlappedActor = OtherActor;
	GetWorldTimerManager().SetTimer(LoopTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (--LoopTime <= 0)
			{
				GetWorldTimerManager().ClearTimer(LoopTimerHandle);
				LoopTime = 10;
				LineTrace(OverlappedActor);
			}
			UE_LOG(LogTemp, Warning,TEXT("%d"), a++);
			UGameplayStatics::SpawnSoundAtLocation(this, TimeSound, this->GetActorLocation());
		}), 0.1f, true);





}

// Called when the game starts or when spawned
void ABTS_C4::BeginPlay()
{
	Super::BeginPlay();

	ProgressWidget = Cast<UBTS_InteractionProgress>(ProgressBar->GetUserWidgetObject());

}

// Called every frame
void ABTS_C4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!WidgetVisible)
	{
		
		float ElapesdTime = GetWorldTimerManager().GetTimerElapsed(TimerHandle);

		float Percent = ElapesdTime / ClearTimer;
		ProgressWidget->SetPercent(Percent);
	}
}

void ABTS_C4::LineTrace(AActor* OtherActor)
{
	FHitResult Res;

	FVector To = OtherActor->GetActorLocation();
	FVector From = GetActorLocation();

	FVector End = ((To - From).GetSafeNormal() * 100) + To;

	GetWorld()->LineTraceSingleByChannel(Res, GetActorLocation(), End,ECollisionChannel::ECC_Camera);
	
	if (ABTS_CharacterBase* Character = Cast<ABTS_CharacterBase>(Res.GetActor()))
	{
		if (UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent())
		{
			float distance = Character->GetDistanceTo(this) / ExplosionEffectiveDistance;
			Explosion(ASC, distance);
		}

	}
	else
	{
		if (ABTS_CharacterBase* ohterCharacter = Cast<ABTS_CharacterBase>(OtherActor))
		{
			if (UAbilitySystemComponent* ASC = ohterCharacter->GetAbilitySystemComponent())
			{
				float distance = ohterCharacter->GetDistanceTo(this) / ExplosionEffectiveDistance;
				distance += 0.5;

				Explosion(ASC, distance);
			}
		}
	
	}



}

void ABTS_C4::Explosion(UAbilitySystemComponent* ASC,float EffectLevel)
{
	const FGameplayEffectSpecHandle spec = ASC->MakeOutgoingSpec(ExplosionEffect, EffectLevel, ASC->MakeEffectContext());

	FBTS_GameplayTags GameplayTag = FBTS_GameplayTags::Get();
	
	float FinalDamage = ExplosionDamage - (10 * (EffectLevel-1));
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(spec, GameplayTag.ExplosionDamage, FinalDamage);


	FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*(spec.Data.Get()));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle.Get(), C4Mesh->GetComponentTransform());

	Destroy();
}

