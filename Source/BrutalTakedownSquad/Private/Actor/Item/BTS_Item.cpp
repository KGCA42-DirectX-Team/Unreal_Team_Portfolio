
#include "Actor/Item/BTS_Item.h"

ABTS_Item::ABTS_Item()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	CollisionVolume->SetSphereRadius(50.f);
	CollisionVolume->SetupAttachment(RootComponent);

	CollisionVolume->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionVolume->SetGenerateOverlapEvents(true);
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ABTS_Item::OnPickUpOverlap);
}

void ABTS_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_Item::OnPickUpOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ItemOwner = CastChecked<ABTS_CharacterBase>(OtherActor);
	if(!ItemOwner) return;
	if(!ItemOwner->HasAuthority()) return;

	ItemOwner->GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(CommonAbilityClass));
}

