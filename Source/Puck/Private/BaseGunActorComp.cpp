// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGunActorComp.h"
#include "PuckSlayer.h"
#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UBaseGunActorComp::UBaseGunActorComp()
{
	// Set this component to be initialiAzed when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UBaseGunActorComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AController* ownerController = ownerPlayer->GetController();
	if(ownerController)
	{
		playerController = Cast<APlayerController>(ownerController);
		
		if(ownerPlayer)
		{
			TArray<UArrowComponent*> ArrowComponents;
			ownerPlayer->GetComponents<UArrowComponent>(ArrowComponents);

			for(UArrowComponent* singleArrow : ArrowComponents)
			{
				if(singleArrow->GetName() == "FireArrowComp")
				{
					fireArrow = singleArrow;
				}
			}
		}
	}
}


// Called every frame
void UBaseGunActorComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBaseGunActorComp::InitOption()
{
	//UE_LOG(LogTemp, Warning, )
}

//사격
void UBaseGunActorComp::Fire()
{
	_startLoc = fireArrow->GetComponentLocation();
	_endLoc = _startLoc + fireArrow->GetForwardVector() * Range;
}

//장전
void UBaseGunActorComp::Reload()
{
	if(IsFullMagazine())
	{
		return;
	}
	
	CurrentMagazine++;
}

void UBaseGunActorComp::EndFire()
{
}

//탄환이 다 찼는지
bool UBaseGunActorComp::IsFullMagazine()
{
	if(CurrentMagazine >= MaxMagazine)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//ActorComponent를 장착한 Actor
ACharacter* UBaseGunActorComp::GetOwnerPlayer()
{
	return ownerPlayer;
}
