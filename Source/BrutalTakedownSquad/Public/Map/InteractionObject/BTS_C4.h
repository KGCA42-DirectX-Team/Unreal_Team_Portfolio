// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interface/BTS_InteractionInterface.h"
#include "BTS_C4.generated.h"

class USphereComponent;
class UWidgetComponent;
class UBTS_InteractionProgress;
class UGameplayEffect;

UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_C4 : public AActor , public IBTS_InteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABTS_C4();


	virtual void Visible_Implementation() override;

	virtual void Interaction_Implementation() override;

	virtual void InteractionClear_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void TriggerLineOverlap(AActor* OtherActor);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> C4Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> TriggerLine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> Clearwidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> ProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USoundBase> TimeSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ExplosionEffect;


	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> ExplosionParticle;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBTS_InteractionProgress> ProgressWidget;

	UPROPERTY(BlueprintReadOnly)
	bool WidgetVisible = true;
	UPROPERTY(BlueprintReadOnly)
	float ClearTimer = 3.0f;
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle TimerHandle;

private:
	int LoopTime = 2;

	float ExplosionDamage = 20.0f;

	FTimerHandle LoopTimerHandle;

	float ExplosionEffectiveDistance = 100.0f;

	AActor* OverlappedActor;

	

	TArray<FName> BoneName;
	void LineTrace(AActor* OtherActor);
	void Explosion();

};
