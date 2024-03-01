


#include "Actor/BTS_WeaponTest.h"
#include "Character/Player/BTS_Player.h"
#include "Actor/BTS_Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


UBTS_WeaponTest::UBTS_WeaponTest()
{
	
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}


void UBTS_WeaponTest::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			
			World->SpawnActor<ABTS_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}

	
	if (FireAnimation != nullptr)
	{
		
		//UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		//if (AnimInstance != nullptr)
		//{
		//	AnimInstance->Montage_Play(FireAnimation, 1.f);
		//}
	}
}

/*
void UBTS_WeaponTest::AttachWeapon(ABTS_Player* TargetCharacter)
{
	Character = TargetCharacter;

	
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	
	Character->SetHasRifle(true);

	
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UBTS_WeaponTest::Fire);
		}
	}
}
*/

void UBTS_WeaponTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}