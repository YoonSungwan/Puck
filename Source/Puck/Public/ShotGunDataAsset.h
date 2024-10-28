// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponDataAsset.h"
#include "ShotGunDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PUCK_API UShotGunDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunData")
	int32 BulletNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunData")
	float PitchCongestion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunData")
	float RollCongestion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunData")
	float YawCongestion;

	UFUNCTION()
	void ShotGunFire();
};
