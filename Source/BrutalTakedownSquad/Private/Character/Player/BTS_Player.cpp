
#include "Character/Player/BTS_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Player/BTS_PlayerState.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "Character/Player/BTS_PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/HUD/BTS_PlayerHUD.h"
#include "MotionWarpingComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystem/BTS_AttributeSet.h"

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

	// Create Components
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
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

void ABTS_Player::BeginPlay()
{
	Super::BeginPlay();

	OnCharacterDie.AddUObject(this, &ABTS_Player::PlayerDie);
}

void ABTS_Player::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckHitSurfaceWhileSlide();
	CheckRemainStemina();
}

void ABTS_Player::InitAbilityActorInfo()
{
	ABTS_PlayerState* BTSPlayerState = GetPlayerState<ABTS_PlayerState>();
	check(BTSPlayerState);

	UBTS_AbilitySystemComponent* ASC = CastChecked<UBTS_AbilitySystemComponent>(BTSPlayerState->GetAbilitySystemComponent());

	ASC->InitAbilityActorInfo(BTSPlayerState, this);

	AbilitySystemComponent = ASC;
	AttributeSet = BTSPlayerState->GetAttributeSet();

	InitializeDefaultAttributes();

	// Init HUD
	if (ABTS_PlayerController* BTSPlayerController = Cast<ABTS_PlayerController>(GetController()))
	{
		if (ABTS_PlayerHUD* PlayerHUD = Cast<ABTS_PlayerHUD>(BTSPlayerController->GetHUD()))
		{
			PlayerHUD->InitOverlay(BTSPlayerController, BTSPlayerState, AttributeSet, AbilitySystemComponent);
		}
	}
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
		, IgnoredActors, EDrawDebugTrace::None, HitResult, true)) 
	{
		if(FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(HitResult.ImpactPoint , FVector::ZAxisVector))) > 80) // angle : 80
		{
			ActivateAbilityByTag(FGameplayTag().RequestGameplayTag("Ability.Conditional.EndSlide"));
		}
	} 


}

void ABTS_Player::CheckRemainStemina()
{
	if (UBTS_AttributeSet* AS = Cast<UBTS_AttributeSet>(GetAttributeSet()))
	{
		if (AS->GetStamina() <= 1)
		{
			ActivateAbilityByTag(FGameplayTag().RequestGameplayTag("Ability.Conditional.EndSprint"));
		}
	}
}
