// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleFireActorComp.h"
#include "CS_RifleRecoil.h"
#include "PuckSlayer.h"
#include "Kismet/GameplayStatics.h"

URifleFireActorComp::URifleFireActorComp()
{
	Damage = 10;
	Range = 3500;
	MaxMagazine = 100;
	CurrentMagazine = MaxMagazine;
}

void URifleFireActorComp::InitOption()
{
	Super::InitOption();
}

void URifleFireActorComp::Fire()
{
	Super::Fire();

	if(!ownerPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Fire because No ownerPlayer"));
		return;
	}

	FHitResult _hitRes;

	FCollisionQueryParams _collisionParam;
	_collisionParam.AddIgnoredActor(ownerPlayer);

	//반동
	float yawRandom = FMath::RandRange(-0.3, 0.3);
	float pitchRandom = FMath::RandRange(-0.2, 0.1);
	
	_endLoc.X += pitchRandom;
	_endLoc.Z += yawRandom;
	
	playerController->AddYawInput(yawRandom);
	playerController->AddPitchInput(pitchRandom);
		
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(UCS_RifleRecoil::StaticClass());

	//LineTrace
	bool isHit = GetWorld()->LineTraceSingleByChannel(_hitRes, _startLoc, _endLoc, ECC_Pawn, _collisionParam);
	DrawDebugLine(GetWorld(), _startLoc, _endLoc, FColor::Green, true, 3.f);
		
	if(isHit)
	{
		AActor* hitActor = _hitRes.GetActor();
		if(hitActor)
		{
			UGameplayStatics::ApplyDamage(hitActor, Damage, ownerPlayer->GetController(), ownerPlayer, UDamageType::StaticClass());
			
			FVector actorLocation = _hitRes.Location;

			if (particleEffect)
			{
				FVector newShootScale(1.3f, 1.3f, 1.3f);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleEffect, actorLocation, FRotator::ZeroRotator, newShootScale, true);
			}
		}
	}

	EndFire();
}

void URifleFireActorComp::EndFire()
{
	Super::EndFire();
}
