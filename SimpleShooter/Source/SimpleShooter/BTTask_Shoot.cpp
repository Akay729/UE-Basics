// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterCharacter.h"
#include "AIController.h"


UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr) return EBTNodeResult::Failed;
    
    AShooterCharacter* ControllerPawn = Cast<AShooterCharacter>(AIController->GetPawn());
    if (ControllerPawn == nullptr) return EBTNodeResult::Failed;
    
    ControllerPawn->FireAction();

    return EBTNodeResult::Succeeded;
}