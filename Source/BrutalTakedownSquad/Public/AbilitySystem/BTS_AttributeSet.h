
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BTS_AttributeSet.generated.h"

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

// Player AttributeSet
// Admin: YWS
UCLASS()
class BRUTALTAKEDOWNSQUAD_API UBTS_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBTS_AttributeSet();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attribures")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attribures")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Default Attribures")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Default Attribures")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, MaxStamina); 

	// meta attribute
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attribures")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, IncomingDamage)

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attribures")
	FGameplayAttributeData DefansePower;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, DefansePower)

	// ammo max value는 귀찮으니까 따로 만들지 않음
	UPROPERTY(BlueprintReadOnly, Category = "Ammo Attribures")
	FGameplayAttributeData Ammo_9mm;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, Ammo_9mm)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo Attribures")
	FGameplayAttributeData Ammo_5mm;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, Ammo_5mm)

	UPROPERTY(BlueprintReadOnly, Category = "Ammo Attribures")
	FGameplayAttributeData Ammo_7mm;
	ATTRIBUTE_ACCESSORS(UBTS_AttributeSet, Ammo_7mm)


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

	void HandleIncomingDamage(const FEffectProperties& Props);

};
