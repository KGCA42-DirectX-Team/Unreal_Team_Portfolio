
#include "Character/Player/BTSPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Input/BTSInputComponent.h"
#include "AbilitySystem/BTSAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../BTSGameplayTags.h"


ABTSPlayerController::ABTSPlayerController()
{
	bReplicates = true;
}

void ABTSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ABTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(BTSContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(BTSContext, 0);
	}

	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	InputModeData.SetHideCursorDuringCapture(true);
	SetInputMode(InputModeData);
}

void ABTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UBTSInputComponent* BTSInputComponent = CastChecked<UBTSInputComponent>(InputComponent);

	BTSInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABTSPlayerController::Move);

	BTSInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHold);
}

void ABTSPlayerController::Move(const FInputActionValue& InputActionValue)
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

void ABTSPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	UBTSAbilitySystemComponent* BTSASC = GetASC();

	if (BTSASC)
		BTSASC->AbilityInputTagPressed(InputTag);
}

void ABTSPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	UBTSAbilitySystemComponent* BTSASC = GetASC();

	if (BTSASC)
		BTSASC->AbilityInputTagReleased(InputTag);
}

void ABTSPlayerController::AbilityInputTagHold(FGameplayTag InputTag)
{
	UBTSAbilitySystemComponent* BTSASC = GetASC();

	if (BTSASC)
		BTSASC->AbilityInputTagHold(InputTag);
}

UBTSAbilitySystemComponent* ABTSPlayerController::GetASC()
{
	if (BTSAbilitySystemComponent == nullptr)
	{
		BTSAbilitySystemComponent = Cast<UBTSAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return BTSAbilitySystemComponent;
}
