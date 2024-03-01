
#include "Character/Player/BTS_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/BTS_PlayerState.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "Character/Player/BTS_PlayerController.h"

ABTS_Player::ABTS_Player()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ABTS_Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// init ability actor info for server
	InitAbilityActorInfo();

	AddCharacterAbilities();
}

void ABTS_Player::OnRep_PlayerState()
{
	// this is required when replicating the player state
	//Super::OnRep_PlayerState();
	//
	//// init ability actor info for client
	//InitAbilityActorInfo();
}

float ABTS_Player::GetTurnRate()
{
	ABTS_PlayerController* PlayerController = Cast<ABTS_PlayerController>(GetController());

	if (PlayerController)
	{
		return PlayerController->GetTurnRate();
	}

	return 0.0f;
}

void ABTS_Player::InitAbilityActorInfo()
{
	ABTS_PlayerState* BTSPlayerState = GetPlayerState<ABTS_PlayerState>();
	check(BTSPlayerState);

	UBTS_AbilitySystemComponent* ASC = CastChecked<UBTS_AbilitySystemComponent>(BTSPlayerState->GetAbilitySystemComponent());

	ASC->InitAbilityActorInfo(BTSPlayerState, this);

	AbilitySystemComponent = ASC;
	AttributeSet = BTSPlayerState->GetAttributeSet();

	//// Init HUD
	//if (ABTS_PlayerController* BTSPlayerController = Cast<ABTS_PlayerController>(GetController()))
	//{
	//	if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
	//	{
	//		AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
	//	}
	//}

	InitializeDefaultAttributes();
}
