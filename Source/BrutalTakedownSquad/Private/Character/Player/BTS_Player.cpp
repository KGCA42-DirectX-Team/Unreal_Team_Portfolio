
#include "Character/Player/BTS_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/BTS_PlayerState.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "Character/Player/BTS_PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

// temp
#include "BTS_GameplayTags.h"

ABTS_Player::ABTS_Player()
{
	PrimaryActorTick.bCanEverTick = true;

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

float ABTS_Player::GetTurnRate_Implementation()
{
	ABTS_PlayerController* PlayerController = Cast<ABTS_PlayerController>(GetController());

	if (PlayerController)
	{
		return PlayerController->GetTurnRate();
	}

	return 0.0f;
}

void ABTS_Player::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//CheckHitSurfaceWhileSlide();
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

void ABTS_Player::CheckHitSurfaceWhileSlide()
{
	// socket, radius, angle is constant

	FVector FootPosition = GetMesh()->GetSocketLocation("foot_l"); // socket : foot_l
	
	TArray<AActor*> IgnoredActors; 
	IgnoredActors.Add(this);
	IgnoredActors.Add(GetCharacterMovement()->CurrentFloor.HitResult.GetActor());

	FHitResult HitResult;
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), FootPosition, FootPosition, 25 // radius : 25
		, UEngineTypes::ConvertToTraceType(ECC_Visibility), false
		, IgnoredActors, EDrawDebugTrace::ForOneFrame, HitResult, true)) 
	{
		if(FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(HitResult.ImpactPoint , FVector::ZAxisVector))) > 80) // angle : 80
		{
			ActivateAbilityByTag(FBTS_GameplayTags::Get().InputTag_G);
		}
	} 
}
