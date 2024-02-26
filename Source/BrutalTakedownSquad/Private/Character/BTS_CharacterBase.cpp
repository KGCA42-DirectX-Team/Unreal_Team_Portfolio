
#include "Character/BTS_CharacterBase.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"

ABTS_CharacterBase::ABTS_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

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

void ABTS_CharacterBase::Die()
{
	// if all item drop on death these code will not be used
	//Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	//// drop weapon
	//Weapon->SetSimulatePhysics(true);
	//Weapon->SetEnableGravity(true);
	//Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	// Ragdoll
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	// Disable capsule collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
}

UAnimMontage* ABTS_CharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

UAbilitySystemComponent* ABTS_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABTS_CharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

