// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGunActorComp.h"
#include "PuckSlayer.h"
#include "RifleDataAsset.h"
#include "ShotGunDataAsset.h"
#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UBaseGunActorComp::UBaseGunActorComp()
{
	// Set this component to be initialiAzed when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//데이터 에셋 불러오기
	TArray<FString> FireName;
	this->GetName().ParseIntoArray(FireName, TEXT("__"));
	TArray<FString> DaSplit;
	UE_LOG(LogTemp, Warning, TEXT("%s find Error"), *FireName[0]);
	UE_LOG(LogTemp, Warning, TEXT("%s find Error"), *FireName[1]);
	FireName[1].ParseIntoArray(DaSplit,TEXT("Fire"));
	
	FString AssetPath = FString("/Game/DataAssets/DA_").Append(DaSplit[0]).Append(".DA_").Append(DaSplit[0]);
	FSoftObjectPath SoftObjPath(AssetPath);
	TSoftObjectPtr<UDataAsset> SoftObjPtr = TSoftObjectPtr<UDataAsset>(SoftObjPath);

	if(GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("GoGo Delegate"));
		ownerPlayer = Cast<APuckSlayer>(GetOwner());
	}
}


// Called when the game starts
void UBaseGunActorComp::BeginPlay()
{
	Super::BeginPlay();

	if(ownerPlayer)
	{
		ownerPlayer->OnFireDelegate.AddDynamic(this, &UBaseGunActorComp::Fire);	
	}

	// ...
	AController* ownerController = ownerPlayer->GetController();
	if(ownerController)
	{
		if(Cast<APlayerController>(ownerController))
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

//사격
void UBaseGunActorComp::Fire()
{
	UE_LOG(LogTemp, Error, TEXT("DataAsset Fire is Start"));
	if(!WeaponDataAsset)
	{
		UE_LOG(LogTemp, Error, TEXT("DataAsset is not valid"));
		return;
	}

	if(UShotGunDataAsset* DA_Shotgun = Cast<UShotGunDataAsset>(WeaponDataAsset))
	{
		DA_Shotgun->ShotGunFire();
	}
	else if(URifleDataAsset* DA_Rifle = Cast<URifleDataAsset>(WeaponDataAsset))
	{
		DA_Rifle->RifleFire();
	}
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
