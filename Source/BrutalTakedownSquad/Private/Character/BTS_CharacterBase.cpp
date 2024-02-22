
#include "Character/BTS_CharacterBase.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"

ABTS_CharacterBase::ABTS_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABTS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABTS_CharacterBase::InitAbilityActorInfo()
{
}

void ABTS_CharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultAttribute);
	ApplyEffectToSelf(VitalAttribute);
}

void ABTS_CharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	check(IsValid(ASC));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1, ContextHandle);
	ASC->ApplyGameplayEffectSpecToTarget(*(SpecHandle.Data.Get()), ASC);
}

void ABTS_CharacterBase::AddCharacterAbilities() const
{
	UBTS_AbilitySystemComponent* BTSASC = CastChecked<UBTS_AbilitySystemComponent>(AbilitySystemComponent);

	if (!HasAuthority())
		return;

	BTSASC->AddCharacterAbilities(StartupAbilities);
}

UAbilitySystemComponent* ABTS_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABTS_CharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

