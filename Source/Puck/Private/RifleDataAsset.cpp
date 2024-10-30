// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleDataAsset.h"

#include "CS_RifleRecoil.h"
#include "PuckSlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

void URifleDataAsset::RifleFire()
{
	UE_LOG(LogTemp, Warning, TEXT("RifleFire Start..."));
	FVector _startLoc = FireArrow->GetComponentLocation();
	FVector _endLoc = _startLoc + FireArrow->GetForwardVector() * Range;

	FHitResult _hitRes;

	FCollisionQueryParams _collisionParam;
	_collisionParam.AddIgnoredActor(OwnerPlayer);

	float yawRandom = FMath::RandRange(-0.3, 0.3);
	float pitchRandom = FMath::RandRange(-0.2, 0.1);

	/*if(bIsAiming)
	{
		_endLoc.X += pitchRandom;
		_endLoc.Z += yawRandom;
	}
	else
	{
		playerController->AddYawInput(yawRandom);
		playerController->AddPitchInput(pitchRandom);
	}*/
		
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(UCS_RifleRecoil::StaticClass());
		
	bool isHit = GetWorld()->LineTraceSingleByChannel(_hitRes, _startLoc, _endLoc, ECC_Pawn, _collisionParam);
	//DrawDebugLine(GetWorld(), _startLoc, _endLoc, FColor::Green, true, 5.f);
		
	if(isHit)
	{
		AActor* hitActor = _hitRes.GetActor();
		if(hitActor)
		{
			UGameplayStatics::ApplyDamage(hitActor, Damage, OwnerPlayer->GetController(), OwnerPlayer, UDamageType::StaticClass());

			//FVector actorLocation = hitActor->GetActorLocation();
			FVector actorLocation = _hitRes.Location;


			if (particleEffect)
			{
				FVector newShootScale(1.3f, 1.3f, 1.3f);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleEffect, actorLocation, FRotator::ZeroRotator, newShootScale, true);
			}
		}
	}
}
