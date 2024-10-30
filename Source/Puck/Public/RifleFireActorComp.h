// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGunActorComp.h"
#include "RifleFireActorComp.generated.h"

/**
 * 
 */
UCLASS()
class PUCK_API URifleFireActorComp : public UBaseGunActorComp
{
	GENERATED_BODY()

public:
	URifleFireActorComp();
	
	void Fire() override;

	void EndFire() override;
	
};
