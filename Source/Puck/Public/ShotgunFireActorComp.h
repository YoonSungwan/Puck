// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGunActorComp.h"
#include "ShotgunFireActorComp.generated.h"

/**
 * 
 */
UCLASS()
class PUCK_API UShotgunFireActorComp : public UBaseGunActorComp
{
	GENERATED_BODY()

public:
	UShotgunFireActorComp();
	
	int32 BulletNum = 6;

	UPROPERTY(EditAnywhere, Category="bullet option")
	float PitchCongestion = 200;
	
	UPROPERTY(EditAnywhere, Category="bullet option")
	float RollCongestion = 200;

	UPROPERTY(EditAnywhere, Category="bullet option")
	float YawCongestion = 200;

public:
	
	void Fire() override;

	void EndFire() override;
	
};
