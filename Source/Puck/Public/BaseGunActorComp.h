// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireInterface.h"
#include "ReloadInterface.h"
#include "BaseGunActorComp.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUCK_API UBaseGunActorComp : public UActorComponent, public IFireInterface, public IReloadInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseGunActorComp();

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* particleEffect; // 파티클 이펙트 변수

	UParticleSystemComponent* particleComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FireArrow")
	class UArrowComponent* fireArrow;

	UPROPERTY(EditAnywhere, Category="bullet option")
	float Damage;

	UPROPERTY(EditAnywhere, Category="bullet option")
	float Range;

	UPROPERTY(EditAnywhere, Category="bullet option")
	int MaxMagazine;

	UPROPERTY(EditAnywhere, Category="bullet option")
	int CurrentMagazine;

	APlayerController* playerController;
	class APuckSlayer* ownerPlayer;

	FVector _startLoc;
	FVector _endLoc;
	
private:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitOption();

	virtual void Fire() override;
	virtual void Reload() override;

	virtual void EndFire();
	
	ACharacter* GetOwnerPlayer();

	bool IsFullMagazine();
};
