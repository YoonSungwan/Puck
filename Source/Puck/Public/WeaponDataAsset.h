// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
class APuckSlayer;
class UArrowComponent;
UCLASS()
class PUCK_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	class APuckSlayer* OwnerPlayer;

	UPROPERTY()
	class UArrowComponent* FireArrow;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* particleEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GunData")
    FName GunName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GunData")
	float Range;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GunData")
    int32 Damage;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GunData")
    int32 Magazine;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GunData")
    int32 MaxMagazine;    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GunData")
    USkeletalMesh* WeaponMesh; 
};
