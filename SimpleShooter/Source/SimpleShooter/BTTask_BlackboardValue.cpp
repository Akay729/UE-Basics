// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BlackboardValue::UBTTask_BlackboardValue()
{
    NodeName = TEXT("Clear Blackboard Value");
}


EBTNodeResult::Type UBTTask_BlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    FName SelectedKey = GetSelectedBlackboardKey();
    // Clear the value assign to it
    OwnerComp.GetBlackboardComponent()->ClearValue(SelectedKey);
    return EBTNodeResult::Succeeded;
}