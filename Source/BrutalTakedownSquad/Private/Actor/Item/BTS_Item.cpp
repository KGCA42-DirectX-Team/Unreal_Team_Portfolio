
#include "Actor/Item/BTS_Item.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "Components/SphereComponent.h"

ABTS_Item::ABTS_Item()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComp"));
	SetRootComponent(RootSceneComp);

	InteractiveRegion = CreateDefaultSubobject<USphereComponent>(TEXT("InteractiveRegion"));
	InteractiveRegion->SetSphereRadius(140.f);
	InteractiveRegion->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	InteractiveRegion->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractiveRegion->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractiveRegion->SetGenerateOverlapEvents(true);
	InteractiveRegion->OnComponentBeginOverlap.AddDynamic(this, &ABTS_Item::OnInsidePickUpDistance);
	InteractiveRegion->OnComponentEndOverlap.AddDynamic(this, &ABTS_Item::OnOutsidePickUpDistance);

	InteractiveRegion->SetupAttachment(RootComponent);
}

void ABTS_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_Item::OnInsidePickUpDistance(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bIsPickableToPlayer = true;
}

void ABTS_Item::OnOutsidePickUpDistance(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsPickableToPlayer = false;
}

void ABTS_Item::OnPickUp(UAbilitySystemComponent* ASC)
{
	UBTS_AbilitySystemComponent* BTS_ASC = CastChecked<UBTS_AbilitySystemComponent>(ASC);

	BTS_ASC->AddCharacterAbility(SharedAbilityClass);     

}

void ABTS_Item::OnDrop(UAbilitySystemComponent* ASC)
{

}

void ABTS_Item::SetItemTypeTag(FGameplayTag NewTag)
{
	ItemTypeTag = NewTag;
}
