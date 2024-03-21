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
	BoneName.Add(FName("spine_04"));
	BoneName.Add(FName("head"));
	BoneName.Add(FName("pelvis"));
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
				LoopTime = 15;
				LineTrace(OverlappedActor);
			}
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

	FVector Start = GetActorLocation();
	TArray<AActor*> Ignore;
	FHitResult Res;

	
	FVector From = GetActorLocation();


	Ignore.Add(this);
	if (ABTS_CharacterBase* Character = Cast<ABTS_CharacterBase>(OtherActor))
	{
		for (const FName& Name : BoneName)
		{
			UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();

			FVector To = Character->GetMesh()->GetSocketLocation(Name);
			FVector End = ((To - From).GetSafeNormal()*500)+ From;

			if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceTypeQuery2, false,
				Ignore, EDrawDebugTrace::ForDuration, Res, true))
			{
				if (Res.GetActor() == OtherActor)
				{
					const FGameplayEffectSpecHandle spec = ASC->MakeOutgoingSpec(ExplosionEffect, 0, ASC->MakeEffectContext());

					FBTS_GameplayTags GameplayTag = FBTS_GameplayTags::Get();

					UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(spec, GameplayTag.Attributes_ExplosionDamage, ExplosionDamage);

					FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*(spec.Data.Get()));
				}

			}

		}

	}
	
	Explosion();



}

void ABTS_C4::Explosion()
{

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle.Get(), C4Mesh->GetComponentTransform());

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, C4Mesh->GetComponentLocation());

	Destroy();
}

