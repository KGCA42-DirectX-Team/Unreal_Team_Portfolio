
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "BTS_EffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Instant = 1 << 1 UMETA(DisplayName = "Instant"),
	Duration = 1 << 2 UMETA(DisplayName = "Duration"),
	Infinite = 1 << 3 UMETA(DisplayName = "Infinite"),
	ALL = Instant | Duration | Infinite UMETA(DisplayName = "ALL")
};

USTRUCT(BlueprintType)
struct FCallerTagMagnitudesMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, float> TagAndMagnitudes;
};

// Easy to use applying and removing effects on the other actors
// 
// Admim: YWS
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

	UFUNCTION(BlueprintCallable)
	void SetCallerMagnitude(FGameplayTag Tag, float Magnitude, const EEffectType EffectType);

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
