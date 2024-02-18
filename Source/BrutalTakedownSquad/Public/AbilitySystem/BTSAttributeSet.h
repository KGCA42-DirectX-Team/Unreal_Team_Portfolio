
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BTSAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY();
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY();
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY();
	AController* SourceController = nullptr;

	UPROPERTY();
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY();
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY();
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY();
	AController* TargetController = nullptr;

	UPROPERTY();
	ACharacter* TargetCharacter = nullptr;
};

/// <summary>
/// AttributeSet이 상속받아서 사용할 클래스
/// </summary>
/// <remarks>
/// 
/// </remarks>
/// @author 유원석
/// @date last change 2024/02/16
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTSAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBTSAttributeSet();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attribures")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBTSAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attribures")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UBTSAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Default Attribures")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBTSAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Default Attribures")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UBTSAttributeSet, MaxStamina); 

public:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	void SetEffectProperties(FEffectProperties& Props, const FGameplayEffectModCallbackData& Data) const;
};
