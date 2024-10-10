// Fill out your copyright notice in the Description page of Project Settings.


#include "PuckWeaponComponent.h"

#include <filesystem>

#include "BFG_Projectile.h"
#include "PuckSlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FireActorComponent.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Puck/Widgets/HUDUserWidget.h"

UPuckWeaponComponent::UPuckWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	PrimaryComponentTick.bCanEverTick = true;
	Damage = 100.f;
}

bool UPuckWeaponComponent::AttachWeapon(class APuckSlayer* TargetCharacter)
{
	Character = TargetCharacter;
	// Check that the character is valid
	if (Character == nullptr)
	{
		return false;
	}

	// 플레이어가 두 개 미만의 무기를 가지고 있는지 확인
	// 적절한 소켓 이름 결정
	AttachedSocketName = "WeaponSocket";
	if (Character->OwingWeaponNum == 1)
	{
		AttachedSocketName = "WeaponBackSocket";
	}
	else if (Character->OwingWeaponNum > 1)
	{
		return false;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	if (!AttachToComponent(Character->GetMesh(), AttachmentRules, AttachedSocketName))
	{
		return false;
	}
	
	// add the weapon as an instance component to the character
	Character->AddInstanceComponent(this);

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UPuckWeaponComponent::Fire);
			EnhancedInputComponent->BindAction(FireTraceAction, ETriggerEvent::Triggered, this, &UPuckWeaponComponent::FireTrace);
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &UPuckWeaponComponent::Reload);
		}
	}
	Character->OwingWeaponNum++;
	return true;
}

void UPuckWeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	// Try and fire a projectile
	/*if (BFG_ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position

			//bug temp
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Try and play the sound if specified
			if (BFG_FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, BFG_FireSound, Character->GetActorLocation());
			}
			// Try and play a firing animation if specified
			if (BFG_FireAnimation != nullptr)
			{
				// Get the animation object for the arms mesh
				UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
				if (AnimInstance != nullptr)
				{
					AnimInstance->Montage_Play(BFG_FireAnimation, 1.f);
				}
			}
			// Spawn the projectile at the muzzle
			ABFG_Projectile* Projectile = World->SpawnActor<ABFG_Projectile>(BFG_ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (Projectile)
			{
				Projectile->SetDamage(BFG_Damage);
		//		Projectile->ProjectileMovement->bRotationFollowsVelocity = true;
				Projectile->SetActorRotation(SpawnRotation);
			}
		}
	}*/

	APuckSlayer* puckCharac = Cast<APuckSlayer>(Character);
	if (puckCharac != nullptr && puckCharac->CurrentEwType == EWType::Shotgun)
	{
		// FVector SocketLocation;
		// FRotator SocketRotation;
		//
		// GetSocketWorldLocationAndRotation("Muzzle", SocketLocation, SocketRotation);
		//
		// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticle, SocketLocation, SocketRotation);
		
		puckCharac->PlayFireAnim();
	}
	
}

void UPuckWeaponComponent::FireTrace()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	APuckSlayer* puckCharac = Cast<APuckSlayer>(Character);
	if (puckCharac != nullptr && puckCharac->CurrentEwType == EWType::Rifle)
	{
		// FVector SocketLocation;
		// FRotator SocketRotation;
		//
		// GetSocketWorldLocationAndRotation("Muzzle", SocketLocation, SocketRotation);
		//
		// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticle, SocketLocation, SocketRotation);
		
		puckCharac->PlayFireAnim();
	}
}

void UPuckWeaponComponent::Reload()
{
	APuckSlayer* puckCharac = Cast<APuckSlayer>(Character);
	if (puckCharac != nullptr)
	{
		puckCharac->PlayReloadAnim();
	}
}

void UPuckWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
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

/** AttackWeapon 을 사용해 시작하자마자 무기를 들고 있게 함
 * 분명 더 나은 풀이가 있겠지만.. 일단 이렇게 두자
*/
void UPuckWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// auto* PuckSlayer = Cast<APuckSlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// AttachWeapon(PuckSlayer);
}
