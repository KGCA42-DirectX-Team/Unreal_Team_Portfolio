// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "BTS_Projectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

// Projectile Base Class
// Admin: KSW
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_Projectile : public AActor
{
	GENERATED_BODY()
public:	
	ABTS_Projectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	float LifeSpan = 10.0f;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Projectile)
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	TObjectPtr<USphereComponent> Collider;
};
