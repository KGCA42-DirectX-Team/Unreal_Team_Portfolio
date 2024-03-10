
#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "GameplayTagContainer.h"
#include "BTS_PhysicMatCharacterHit.generated.h"

// Character Hit Physical Material
// 
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_PhysicMatCharacterHit : public UPhysicalMaterial
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Hit Zone", meta = (AllowPrivateAccess = "true"))
	FGameplayTag HitZoneTag;

public:
	UFUNCTION(BlueprintCallable, Category = "Hit Zone")
	FGameplayTag GetHitZoneTag() const { return HitZoneTag; }
};
