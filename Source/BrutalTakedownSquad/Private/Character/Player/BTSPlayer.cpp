
#include "Character/Player/BTSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/BTSPlayerState.h"
#include "AbilitySystem/BTSAbilitySystemComponent.h"

ABTSPlayer::ABTSPlayer()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ABTSPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init ability actor info for server
	InitAbilityActorInfo();

	AddCharacterAbilities();
}

void ABTSPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// init ability actor info for client
	InitAbilityActorInfo();
}

void ABTSPlayer::InitAbilityActorInfo()
{
	ABTSPlayerState* BTSPlayerState = GetPlayerState<ABTSPlayerState>();
	check(BTSPlayerState);

	BTSPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BTSPlayerState, this);
	Cast<UBTSAbilitySystemComponent>(BTSPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = BTSPlayerState->GetAbilitySystemComponent();
	AttributeSet = BTSPlayerState->GetAttributeSet();

	//// Init HUD
	//if (ABTSPlayerController* BTSPlayerController = Cast<ABTSPlayerController>(GetController()))
	//{
	//	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
	//	{
	//		AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
	//	}
	//}

	InitializeDefaultAttributes();
}
