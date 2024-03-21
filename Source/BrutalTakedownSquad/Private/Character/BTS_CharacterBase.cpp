
#include "Character/BTS_CharacterBase.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Actor/BTS_WeaponComponent.h"
#include "Actor/BTS_ArmorComponent.h"
#include "UI/InventoryUI/BTS_InventoryComponent.h"
#include "BTS_GameplayTags.h"

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

void ABTS_CharacterBase::ActivateAbilityByTag(FGameplayTag AbilityTag) const
{
	// to do : Activate Ability by Tag
	//AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTag, true);

	for (FGameplayAbilitySpec& AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(AbilityTag))
		{
			AbilitySystemComponent->TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

UBTS_WeaponComponent* ABTS_CharacterBase::GetWeaponComponent() const
{ 
	return WeaponComponent;
}

void ABTS_CharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultAttribute);
	ApplyEffectToSelf(VitalAttribute);
	ApplyEffectToSelf(MetaAttribute);
}

void ABTS_CharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass) const
{
	UBTS_AbilitySystemComponent* ASC = CastChecked<UBTS_AbilitySystemComponent>(GetAbilitySystemComponent());

	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1, ContextHandle);
	ASC->ApplyGameplayEffectSpecToTarget(*(SpecHandle.Data.Get()), ASC);
}

void ABTS_CharacterBase::AddCharacterAbilities() const
{
	check(AbilitySystemComponent);
	if (!HasAuthority())
		return;

	AbilitySystemComponent->AddCharacterAbilities(ActiveAbilities);
	AbilitySystemComponent->AddCharacterAbilities(PassiveAbilities);
	AbilitySystemComponent->AddCharacterAbilities(ConditionalAbilities);

	// active passive 
	for (FGameplayAbilitySpec& AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTag(FBTS_GameplayTags::Get().Ability_Passive))
			AbilitySystemComponent->TryActivateAbility(AbilitySpec.Handle);
	}
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

	// Die Event
	OnCharacterDie.Broadcast();
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

