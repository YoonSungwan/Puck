// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBasicInputActorComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PuckSlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "FireActorComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UPlayerBasicInputActorComponent::UPlayerBasicInputActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	if(APuckSlayer* player = Cast<APuckSlayer>(GetOwner()))
	{
		PlayerSlayer = player;
	}
}


// Called when the game starts
void UPlayerBasicInputActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerBasicInputActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerBasicInputActorComponent::SetupPlayerInputFunction(APuckSlayer* puckSlayer)
{
	/*
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &APuckSlayer::Move);
			EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &APuckSlayer::LookUp);
			EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &APuckSlayer::Turn);
			EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &APuckSlayer::InputJump);
	
			EnhancedInputComponent->BindAction(DashIA, ETriggerEvent::Started, this, &APuckSlayer::DashFunc);
			EnhancedInputComponent->BindAction(ZoomIA, ETriggerEvent::Started, this, &APuckSlayer::ZoomFunc);
			EnhancedInputComponent->BindAction(ZoomIA, ETriggerEvent::Completed, this, &APuckSlayer::ZoomOutFunc);
			EnhancedInputComponent->BindAction(ShotgunIA, ETriggerEvent::Started, this, &APuckSlayer::ChangeToShotgun);
			EnhancedInputComponent->BindAction(RifleIA, ETriggerEvent::Started, this, &APuckSlayer::ChangeToRifle);
	
			// Run Start and End
			EnhancedInputComponent->BindAction(RunIA, ETriggerEvent::Started, this, &APuckSlayer::RunStart);
			EnhancedInputComponent->BindAction(RunIA, ETriggerEvent::Completed, this, &APuckSlayer::RunEnd);
			EnhancedInputComponent->BindAction(ExecutionIA, ETriggerEvent::Started, this, &APuckSlayer::Execution);
		}
	*/
}

void UPlayerBasicInputActorComponent::Move(const FInputActionValue& Value)
{
	if(!PlayerSlayer)
	{
		return;
	}

	const FVector MovementVector = Value.Get<FVector>();
	
	const FRotator Rotation = PlayerSlayer->GetControlRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
	// make rotation matrix by using Controller's Rotation
	const FRotationMatrix RotationMatrix(YawRotation);

	// get move dircetion
	const FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
	const FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);

	const FVector MoveDirection = ForwardVector * MovementVector.Y + RightVector * MovementVector.X;
	PlayerSlayer->AddMovementInput(MoveDirection);
}

void UPlayerBasicInputActorComponent::LookUp(const FInputActionValue& Value)
{
	if(!PlayerSlayer)
	{
		return;
	}
	
	float v;
	if (PlayerSlayer->bIsInvertLookUp)
	{
		v = Value.Get<float>();
	}
	else
	{
		v = Value.Get<float>() * -1;
	}

	
	PlayerSlayer->AddControllerPitchInput(v);
}

void UPlayerBasicInputActorComponent::Turn(const FInputActionValue& Value)
{
	if(!PlayerSlayer)
	{
		return;
	}
	
	const float v = Value.Get<float>();
	PlayerSlayer->AddControllerYawInput(v);
}

void UPlayerBasicInputActorComponent::InputJump(const FInputActionValue& Value)
{
	PlayerSlayer->Jump();
}

void UPlayerBasicInputActorComponent::DashFunc(const FInputActionValue& Value)
{
	if (PlayerSlayer->bIsDashOnCooldown)
	{
		return;
	}
	
	if (PlayerSlayer->DashSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),PlayerSlayer->DashSound, PlayerSlayer->GetActorLocation());
	}
	FVector Velocity = PlayerSlayer->GetCharacterMovement()->Velocity;
	Velocity.Z = 0.0;
	Velocity.Normalize();
	
	FVector LaunchVelocity = Velocity * 1500;
	if (!PlayerSlayer->GetCharacterMovement()->IsFalling())
	{
		PlayerSlayer->GetCharacterMovement()->BrakingFrictionFactor = 0.0f; // 지면 마찰 감소
	}
	PlayerSlayer->LaunchCharacter(LaunchVelocity, true, false);
	
	PlayerSlayer->GetWorldTimerManager().SetTimer(PlayerSlayer->DashTimer, FTimerDelegate::CreateLambda([this]()->void
	{
		PlayerSlayer->GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
	}), 0.5f, false);

	PlayerSlayer->bIsDashOnCooldown = true;
	PlayerSlayer->DashRemainingTime = PlayerSlayer->DashCooldownTime;
}

void UPlayerBasicInputActorComponent::RunStart(const FInputActionValue& Value)
{
	if (PlayerSlayer->bIsDashOnCooldown)
	{
		return;
	}
	
	if (PlayerSlayer->bIsAiming)
	{
		PlayerSlayer->bIsAiming = false;
		PlayerSlayer->SetWidgetVisible(false, PlayerSlayer->CurrentEwType);

		PlayerSlayer->TargetSpringArmLength = PlayerSlayer->DefaultSpringArmLength;
		PlayerSlayer->TargetCameraRelativeLocation = PlayerSlayer->DefaultCameraRelativeLocation;
	}
	//
	
	PlayerSlayer->bIsRunning = true;
	
	if (PlayerSlayer->bIsAiming)
	{
		PlayerSlayer->bIsAiming = false;
	}
	
	PlayerSlayer->GetCharacterMovement()->MaxWalkSpeed = 700.0f;
}

void UPlayerBasicInputActorComponent::RunEnd(const FInputActionValue& Value)
{
	if (PlayerSlayer->bIsDashOnCooldown)
	{
		return;
	}
	
	PlayerSlayer->bIsRunning = false;
	PlayerSlayer->GetCharacterMovement()->MaxWalkSpeed = 350.0f;

	;
}
