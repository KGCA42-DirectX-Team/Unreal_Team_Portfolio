// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BTS_Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ABTS_Projectile::ABTS_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	LifeSpan = 10.f;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	Collider->SetSphereRadius(1.f);
	Collider->BodyInstance.SetCollisionProfileName("Projectile");
	Collider->OnComponentHit.AddDynamic(this, &ABTS_Projectile::OnHit);

	// Players can't walk on it
	Collider->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Collider->CanCharacterStepUpOn = ECB_No;

	SetRootComponent(Collider);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = Collider;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
}

void ABTS_Projectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);
}

void ABTS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_Projectile::Destroyed()
{
	if (!HasAuthority())
	{
		//   
	}
	Super::Destroyed();
}

void ABTS_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}