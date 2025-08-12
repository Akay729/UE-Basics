// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    ACharacter* OwnerCharacter {Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn())};

    if (!IsValid(OwnerCharacter) || !ChargeAttackMontage) return EBTNodeResult::Failed;
    
    OwnerCharacter->PlayAnimMontage(ChargeAttackMontage);
    return EBTNodeResult::Succeeded;
    
}