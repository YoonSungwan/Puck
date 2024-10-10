// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_Portal.h"
#include "PuckSlayer.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABP_Portal::ABP_Portal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));;
	SetRootComponent(BoxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(BoxComp);

	portalNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	portalNiagara->SetupAttachment(BoxComp);
}

// Called when the game starts or when spawned
void ABP_Portal::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABP_Portal::OverlapLevelLoadBeing);
}

void ABP_Portal::OverlapLevelLoadBeing(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APuckSlayer* MyCharacter = Cast<APuckSlayer>(OtherActor);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "DoorCollider::OverlapLevelLoadBeing");
	//Fname은 nullptr 개념이 없기 때문에 "" 체크
	if (OtherActor && LevelToLoad != "")
	{
		//전체 Level을 Load
		//UGameplayStatics::OpenLevel(this, LevelToLoad);

		//streaming option structor : 설정 안 해주면 default
		FLatentActionInfo LatentInfo;
		
		//streaming Level Load
		UGameplayStatics::LoadStreamLevel(this,LevelToLoad, true, true, LatentInfo);
		//UGameplayStatics::UnloadStreamLevel(this, LevelToLoad, LatentInfo, true);
	}
}

// Called every frame
void ABP_Portal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

