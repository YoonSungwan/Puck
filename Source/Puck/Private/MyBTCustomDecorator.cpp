// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTCustomDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTCustomDecorator::UMyBTCustomDecorator()
{
    NodeName = "First Time Only"; // ���ڷ����� �̸�
}

bool UMyBTCustomDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    // �����忡�� bHasWaited ���� Ȯ��
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp && BlackboardComp->GetValueAsBool(TEXT("bHasWaited")) == false)
    {
        // ó�� �����̸� �����忡 true ����
        BlackboardComp->SetValueAsBool(TEXT("bHasWaited"), true);
        return true;  // ó������ ����
    }

    return false; // ���Ŀ��� ������ �������� ����
}