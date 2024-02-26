
#include "Character/Player/BTS_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Input/BTS_InputComponent.h"
#include "AbilitySystem/BTS_AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BTS_GameplayTags.h"


ABTS_PlayerController::ABTS_PlayerController()
{
	bReplicates = true;
}

void ABTS_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ABTS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(BTSContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(BTSContext, 0);
	}

	// ??
	//bShowMouseCursor = false;
	//DefaultMouseCursor = EMouseCursor::Default;
	//
	//FInputModeGameAndUI InputModeData;
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	//InputModeData.SetHideCursorDuringCapture(true);
	//SetInputMode(InputModeData);
}

void ABTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UBTS_InputComponent* BTSInputComponent = CastChecked<UBTS_InputComponent>(InputComponent);

	BTSInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABTS_PlayerController::Move);
	BTSInputComponent->BindAction(LookAction, ETriggerEvent::Triggered , this, &ABTS_PlayerController::Look);

	BTSInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHold);
}

void ABTS_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D Axis = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, Axis.Y);
		ControlledPawn->AddMovementInput(RightDirection, Axis.X);
	}
}

void ABTS_PlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D Axis = InputActionValue.Get<FVector2D>();

	AddYawInput(Axis.X);
	AddPitchInput(Axis.Y);
}

void ABTS_PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	UBTS_AbilitySystemComponent* ASC = GetBTS_AbilitySystemComponent();

	if (ASC) ASC->AbilityInputTagPressed(InputTag);
}

void ABTS_PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	UBTS_AbilitySystemComponent* ASC = GetBTS_AbilitySystemComponent();

	if (ASC) ASC->AbilityInputTagReleased(InputTag);
}

void ABTS_PlayerController::AbilityInputTagHold(FGameplayTag InputTag)
{
	UBTS_AbilitySystemComponent* ASC = GetBTS_AbilitySystemComponent();

	if (ASC) ASC->AbilityInputTagHold(InputTag);
}

UBTS_AbilitySystemComponent* ABTS_PlayerController::GetBTS_AbilitySystemComponent()
{
	if (AbilitySystemComponent == nullptr)
	{
		UAbilitySystemComponent* RawASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>());
		AbilitySystemComponent = CastChecked<UBTS_AbilitySystemComponent>(RawASC);
	}

	return AbilitySystemComponent;
}
