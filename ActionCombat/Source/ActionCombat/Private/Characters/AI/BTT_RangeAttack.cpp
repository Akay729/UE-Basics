// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    
    ACharacter* OwnerCharacter { OwnerComp.GetAIOwner()->GetCharacter() };
    if (!IsValid(OwnerCharacter) || !RangeAttackMontage) return EBTNodeResult::Failed;
    
	//Check if is too close
    float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"));
    if (Distance < MeleeRange)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Melee);
        AbortTask(OwnerComp, NodeMemory);
        return EBTNodeResult::Aborted;
    }

    OwnerCharacter->PlayAnimMontage(RangeAttackMontage);
    //UE_LOG(LogTemp, Warning, TEXT("DONE RANGE ATTACK"));
    
    double RandomValue { UKismetMathLibrary::RandomFloat()};
    if(RandomValue > Threshold)
    {
        Threshold = 0.9;
        OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Charge);
    }
    else
    {
        Threshold -= 0.1;
    }
    
    return EBTNodeResult::Succeeded;
}