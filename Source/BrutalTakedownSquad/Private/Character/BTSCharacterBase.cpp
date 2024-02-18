
#include "Character/BTSCharacterBase.h"
#include "AbilitySystem/BTSAbilitySystemComponent.h"

ABTSCharacterBase::ABTSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABTSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABTSCharacterBase::InitAbilityActorInfo()
{
}

void ABTSCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultAttribute);
	ApplyEffectToSelf(VitalAttribute);
}

void ABTSCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass) const
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	check(IsValid(ASC));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1, ContextHandle);
	ASC->ApplyGameplayEffectSpecToTarget(*(SpecHandle.Data.Get()), ASC);
}

void ABTSCharacterBase::AddCharacterAbilities() const
{
	UBTSAbilitySystemComponent* AuraASC = CastChecked<UBTSAbilitySystemComponent>(AbilitySystemComponent);

	if (!HasAuthority())
		return;

	AuraASC->AddCharacterAbilities(StartupAbilities);
}

UAbilitySystemComponent* ABTSCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABTSCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

