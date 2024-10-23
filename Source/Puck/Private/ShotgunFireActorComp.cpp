// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunFireActorComp.h"
#include "PuckSlayer.h"
#include "CS_ShotgunRecoil.h"
#include "Kismet/GameplayStatics.h"

UShotgunFireActorComp::UShotgunFireActorComp()
{
	Damage = 10;
	Range = 2000;
	MaxMagazine = 10;
	CurrentMagazine = MaxMagazine;
}

void UShotgunFireActorComp::InitOption()
{
	Super::InitOption();
	
}


void UShotgunFireActorComp::Fire()
{
	Super::Fire();

	for(int i=0; i < BulletNum; i++)
	{
		FHitResult _hitRes;

		FCollisionQueryParams _collisionParam;
		_collisionParam.AddIgnoredActor(ownerPlayer);
		
		_endLoc.X += FMath::RandRange((PitchCongestion * 0.5) * -1, (PitchCongestion * 0.5));
		_endLoc.Y += FMath::RandRange((RollCongestion * 0.5) * -1, (RollCongestion * 0.5));
		_endLoc.Z += FMath::RandRange((YawCongestion * 0.5) * -1, (YawCongestion * 0.5));	
		
		bool isHit = GetWorld()->LineTraceSingleByChannel(_hitRes, _startLoc, _endLoc, ECC_Pawn, _collisionParam);
		//DrawDebugLine(GetWorld(), _startLoc, _endLoc, FColor::Green, true, 5.f);
		
		if(isHit)
		{
			AActor* hitActor = _hitRes.GetActor();
			if(hitActor)
			{
				UGameplayStatics::ApplyDamage(hitActor, Damage, ownerPlayer->GetController(), ownerPlayer, UDamageType::StaticClass());

				//FVector actorLocation = hitActor->GetActorLocation();
				FVector actorLocation = _hitRes.Location;

					
				if (particleEffect)
				{
					FVector newShootScale(4.0f, 4.0f, 4.0f);
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particleEffect, actorLocation, FRotator::ZeroRotator, newShootScale, true);
				}
			}
		}
	}
	
}

void UShotgunFireActorComp::EndFire()
{
	Super::EndFire();

	//CameraShake
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(UCS_ShotgunRecoil::StaticClass());
}