// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    // SetFocus(PlayerPawn);
    // MoveToActor(PlayerPawn, AdvanceRadius, false);

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);

        //Craezione di una chiave
        UBlackboardComponent* BBComp = GetBlackboardComponent(); 
        if (BBComp)
        {
            BBComp->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        }
        
    }
    
    
    
    //UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    //if (NavSystem == nullptr) return;
} 

void AShooterAIController::Tick(float DelataTime)
{
    Super::Tick(DelataTime);
    
    /* if (LineOfSightTo(PlayerPawn))
    {
        MoveToActor(PlayerPawn, AdvanceRadius, true);
        SetFocus(PlayerPawn);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    } */
    
}