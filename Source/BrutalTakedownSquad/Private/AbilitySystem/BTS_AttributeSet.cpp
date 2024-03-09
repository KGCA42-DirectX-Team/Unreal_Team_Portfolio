
#include "AbilitySystem/BTS_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "Gameframework/Character.h"
#include "AbilitySystemInterface.h"
#include "BTS_GameplayTags.h"
#include "Interface/CombatInterface.h"

UBTS_AttributeSet::UBTS_AttributeSet()
{
}

void UBTS_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBTS_AttributeSet, Health, OldHealth);
}

void UBTS_AttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBTS_AttributeSet, Stamina, OldStamina);
}

void UBTS_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBTS_AttributeSet, MaxHealth, OldMaxHealth);
}

void UBTS_AttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBTS_AttributeSet, MaxStamina, OldMaxStamina);
}

void UBTS_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBTS_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBTS_AttributeSet, Stamina, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UBTS_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBTS_AttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UBTS_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Modifier를 쿼리하여 반환된 값만 변경
	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	else if (Attribute == GetStaminaAttribute())
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	//else if (Attribute == GetIncomingDamageAttribute());
		//NewValue = 0;
}

void UBTS_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Props, Data);

	// effect가 적용된 최종값을 변경
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.0f);

		// damage 계산

		if (LocalIncomingDamage > 0.0f)	// 아직은 치료 효과를 고려하지 않음
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.0f;
			if (!bFatal)
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FBTS_GameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
			else
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);

				if (CombatInterface)
					CombatInterface->Die();
			}

		}
		else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
			SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
			SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}

void UBTS_AttributeSet::SetEffectProperties(FEffectProperties& Props, const FGameplayEffectModCallbackData& Data) const
{	
	// get effect context
	Props.EffectContextHandle = Data.EffectSpec.GetContext();

	// source and target
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		// get target actor
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);

		if (IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(Props.TargetAvatarActor))
		{
			Props.TargetASC = Interface->GetAbilitySystemComponent();
		}
	}
}
