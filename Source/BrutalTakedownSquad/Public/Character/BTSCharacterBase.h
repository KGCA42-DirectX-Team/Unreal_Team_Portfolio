
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "BTSCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

/// <summary>
/// 베이스 캐릭터	 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/15
UCLASS()
class BRUTALTAKEDOWNSQUAD_API ABTSCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABTSCharacterBase();

	// IAbilitySystemInterface을(를) 통해 상속됨
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetIsSprint(bool bNewSprint) { bIsSprint = bNewSprint; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	bool GetIsSprint() const { return bIsSprint; }

protected:
	//UPROPERTY(EditAnywhere, Category = "Combat")
	//TObjectPtr<USkeletalMeshComponent> Weapon1;

	//UPROPERTY(EditAnywhere, Category = "Combat")
	//TObjectPtr<USkeletalMeshComponent> Weapon2;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> VitalAttribute;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass) const;

	void AddCharacterAbilities() const;

private:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	bool bIsSprint = false;
};
