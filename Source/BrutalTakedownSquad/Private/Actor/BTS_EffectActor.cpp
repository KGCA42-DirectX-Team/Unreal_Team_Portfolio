
#include "Actor/BTS_EffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

ABTS_EffectActor::ABTS_EffectActor()
{
}

void ABTS_EffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABTS_EffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABTS_EffectActor::ApplyEffect(AActor* TargetActor)
{
	if (!InstantGameplayEffects.IsEmpty())
	{
		for (auto const EffectPars : InstantGameplayEffects)
		{
			ApplyEffectToTarget(TargetActor, EffectPars.Key, EffectPars.Value);
		}
	}

	if (!DurationGameplayEffects.IsEmpty())
	{
		for (auto const EffectPars : DurationGameplayEffects)
		{
			ApplyEffectToTarget(TargetActor, EffectPars.Key, EffectPars.Value);
		}
	}

	if (!InfiniteGameplayEffects.IsEmpty())
	{
		for (auto const EffectPars : InfiniteGameplayEffects)
		{
			ApplyEffectToTarget(TargetActor, EffectPars.Key, EffectPars.Value);
		}
	}
}

void ABTS_EffectActor::RemoveEffect(AActor* TargetActor)
{
	if (!InfiniteGameplayEffects.IsEmpty())
	{
		if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(TargetActor))
		{
			UAbilitySystemComponent* TargetASC = ASI->GetAbilitySystemComponent();
			if (!TargetASC) 
				return;

			TArray<FActiveGameplayEffectHandle> HandlesToRemove;

			for (auto const EffectPars : InfiniteGameplayEffects)
			{
				for (auto HandlePair : ActiveEffectHandles)
				{
					if (HandlePair.Key.GetOwningAbilitySystemComponent() == TargetASC && HandlePair.Value == EffectPars.Key)
					{
						TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
						HandlesToRemove.Add(HandlePair.Key);
					}
				}
			}

			for (auto& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
}

void ABTS_EffectActor::SetCallerMagnitude(FGameplayTag Tag, float Magnitude,const EEffectType EffectType)
{
	int32 index = 0;
	if ((uint8)EffectType & (uint8)EEffectType::Instant)
	{
		for (auto& EffectPars : InstantGameplayEffects)
		{
			if(EffectPars.Value.TagAndMagnitudes.Contains(Tag))
				EffectPars.Value.TagAndMagnitudes[Tag] = Magnitude;
		}
	}
	if ((uint8)EffectType & (uint8)EEffectType::Duration)
	{
		for (auto& EffectPars : DurationGameplayEffects)
		{
			if (EffectPars.Value.TagAndMagnitudes.Contains(Tag))
				EffectPars.Value.TagAndMagnitudes[Tag] = Magnitude;
		}
	}
	if ((uint8)EffectType & (uint8)EEffectType::Infinite)
	{
		for (auto& EffectPars : InfiniteGameplayEffects)
		{
			if (EffectPars.Value.TagAndMagnitudes.Contains(Tag))
				EffectPars.Value.TagAndMagnitudes[Tag] = Magnitude;
		}
	}
}

void ABTS_EffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, FCallerTagMagnitudesMap TagMagnitudesMap)
{
	if (IAbilitySystemInterface* TargetASI = Cast<IAbilitySystemInterface>(TargetActor))
	{
		UAbilitySystemComponent* TargetASC = TargetASI->GetAbilitySystemComponent();
		if (!TargetASC)
			return;

		FGameplayEffectContextHandle EffectContextHandle;
		EffectContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle;
		if (IAbilitySystemInterface* SourceASI = Cast<IAbilitySystemInterface>(this))
		{
			UAbilitySystemComponent* SourceASC = SourceASI->GetAbilitySystemComponent();
			if (!SourceASC)
				SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

			SpecHandle = SourceASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
		}
		else
			SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

		for (auto const TagMagnitude : TagMagnitudesMap.TagAndMagnitudes)
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(TagMagnitude.Key, TagMagnitude.Value);

		FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*(SpecHandle.Data.Get()));

		// if infinite, add to the map for remove
		const bool bIsInfinite = SpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
		if (bIsInfinite)
			ActiveEffectHandles.Add(ActiveEffectHandle, GameplayEffectClass);
	}
}
