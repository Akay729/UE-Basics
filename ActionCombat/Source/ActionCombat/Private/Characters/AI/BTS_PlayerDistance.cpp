// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTS_PlayerDistance.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTS_PlayerDistance::UBTS_PlayerDistance()
{
    bNotifyTick=true;
}

void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    AAIController* OwnerController = OwnerComp.GetAIOwner();
    APawn* EnemyPawn = OwnerController->GetPawn();
    APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

    FVector EnemyLocation = EnemyPawn->GetActorLocation();
    FVector PlayerLocation = PlayerPawn->GetActorLocation();
    float DistEnemyPlayer = static_cast<float>(FVector::Distance(EnemyLocation, PlayerLocation));
    
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("Distance"), DistEnemyPlayer);
}