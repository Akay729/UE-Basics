// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_MeleeAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Characters/EEnemyState.h"
#include "Navigation//PathFollowingComponent.h"
#include "Interfaces/Fighter.h"

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
    bNotifyTick = true;
    MoveDelegate.BindUFunction(this, "FinishAttackTask");
}

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    bIsFinished = false;
    AAIController* OwnerController = OwnerComp.GetAIOwner();
    
    float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"));


    if (Distance > AttackRadius) 
    {
        bIsFinished = true;
        APawn* PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
        FAIMoveRequest MoveRequest { PlayerActor };
        MoveRequest.SetUsePathfinding(true);
        MoveRequest.SetAcceptanceRadius( AccetableRadius );

        OwnerController->ReceiveMoveCompleted.AddUnique(MoveDelegate);
        OwnerController->MoveTo(MoveRequest);
        OwnerController->SetFocus(PlayerActor);
    }
    else
    {
        IFighter* FighterRef = Cast<IFighter>(OwnerController->GetCharacter());
        FighterRef->Attack();

        FTimerHandle AttackTimerHandle;
        OwnerController->GetCharacter()->GetWorldTimerManager().SetTimer(
            AttackTimerHandle,
            this,
            &UBTT_MeleeAttack::FinishAttackTask,
            FighterRef->GetAnimDuration(),
            false
        );

    }
    

    return EBTNodeResult::InProgress;
}
void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    AAIController* AIRef {OwnerComp.GetAIOwner()};
    float CurrentDistance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"));
    if (CurrentDistance > MeleeRange)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("CurrentState"), EEnemyState::Range);
        AbortTask(OwnerComp, NodeMemory);
        FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);
        
        AIRef->StopMovement();
        AIRef->ClearFocus(EAIFocusPriority::Gameplay);
        AIRef->ReceiveMoveCompleted.Remove(MoveDelegate);
    }

    if (!bIsFinished) return;

    AIRef->ReceiveMoveCompleted.Remove(MoveDelegate);
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    
}

void UBTT_MeleeAttack::FinishAttackTask()
{
    bIsFinished = true;
}