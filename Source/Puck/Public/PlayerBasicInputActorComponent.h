// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "PlayerBasicInputActorComponent.generated.h"

class UInputAction;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PUCK_API UPlayerBasicInputActorComponent : public UActorComponent
{
	GENERATED_BODY()
	

public:
	// Sets default values for this component's properties
	UPlayerBasicInputActorComponent();

	UPROPERTY()
	class APuckSlayer* PlayerSlayer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputFunction(APuckSlayer* puckSlayer);

	void BoundCharacteInputAction(APuckSlayer* puckSlayer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ZoomIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* DashIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ShotgunIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* RifleIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* RunIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ExecutionIA;
	
	void Move(const FInputActionValue& Value);				//플레이어 이동
	void LookUp(const FInputActionValue& Value);			//마우스 좌우
	void Turn(const FInputActionValue& Value);				//마우스 상하
	void InputJump(const FInputActionValue& Value);			//점프
	void DashFunc(const FInputActionValue& Value);			//대쉬
	void RunStart(const FInputActionValue& Value);			//달리기
	void RunEnd(const FInputActionValue& Value);			//달리기 스톱
};
