// Fill out your copyright notice in the Description page of Project Settings.


#include "HookActorComponent.h"

#include "Components/ArrowComponent.h"

// Sets default values for this component's properties
UHookActorComponent::UHookActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//HookMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HookStaticActor"));

	HookArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("HookArrowActor222"));
	
}


// Called when the game starts
void UHookActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("print")), false);
	/*
	if (GetOwner())
	{

		UStaticMeshComponent* TargetMesh = nullptr;
		TArray<UStaticMeshComponent*> MeshComponents;
		GetOwner()->GetComponents<UStaticMeshComponent>(MeshComponents);

		for (UStaticMeshComponent* MeshComponent : MeshComponents)
		{
			if (MeshComponent && MeshComponent->GetName() == FName("CubeStatic"))
			{
				UE_LOG(LogTemp, Warning, TEXT("Find Success"));
				TargetMesh = MeshComponent;
				break;
			}
		}

		if (TargetMesh != nullptr)
		{
			UArrowComponent* testComp = NewObject<UArrowComponent>(GetOwner(), UArrowComponent::StaticClass(), FName("testcomponent"));
			if (HookArrowComp)
			{
				//HookArrowComp->RegisterComponent();
				HookArrowComp->AttachToComponent(TargetMesh, FAttachmentTransformRules::KeepRelativeTransform);

				HookArrowComp->SetRelativeLocation(FVector(10.f));
				UE_LOG(LogTemp, Warning, TEXT("Attach Success"));
			}
		}
	}*/
}


// Called every frame
void UHookActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHookActorComponent::CreateHookLine()
{

}