
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "BTS_EffectActor.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FCallerTagMagnitudesMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, float> TagAndMagnitudes;
};

UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTS_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABTS_EffectActor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	void ApplyEffect(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(AActor* TargetActor);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TMap<TSubclassOf<UGameplayEffect>, FCallerTagMagnitudesMap> InstantGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TMap<TSubclassOf<UGameplayEffect>, FCallerTagMagnitudesMap> DurationGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TMap<TSubclassOf<UGameplayEffect>, FCallerTagMagnitudesMap> InfiniteGameplayEffects;

	TMap<FActiveGameplayEffectHandle, TSubclassOf<UGameplayEffect>> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float ActorLevel = 1.0f;

private:
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, FCallerTagMagnitudesMap TagMagnitudesMap);

};
