// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"


EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    
    ACharacter* OwnerCharacter { Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn<ACharacter>()) };
    if (IsValid(OwnerCharacter) && !RangeAttackMontage) return EBTNodeResult::Failed;
    
    OwnerCharacter->PlayAnimMontage(RangeAttackMontage);
    UE_LOG(LogTemp, Warning, TEXT("DONE RANGE ATTACK"));
	
    return EBTNodeResult::Succeeded;
}