// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponDataAsset.h"
#include "RifleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PUCK_API URifleDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RifleData")
	float PitchRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RifleData")
	float RollRecoil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RifleData")
	float YawRecoil;

	UFUNCTION()
	void RifleFire();
};
