// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    // SetFocus(PlayerPawn);
    // MoveToActor(PlayerPawn, AdvanceRadius, false);

    APawn* OwnerLocation = GetPawn();

    if (AIBehavior)
    {
        RunBehaviorTree(AIBehavior);

        //Craezione di una chiave
        BBComp = GetBlackboardComponent(); 
        if (BBComp)
        {
            //BBComp->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
            BBComp->SetValueAsVector(TEXT("StartLocation"), OwnerLocation->GetActorLocation());
        }
        
    }
    
    //UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    //if (NavSystem == nullptr) return;
} 

void AShooterAIController::Tick(float DelataTime)
{
    Super::Tick(DelataTime);
    
    //No more need to hard code this
    /* if (LineOfSightTo(PlayerPawn))
    {
        if(BBComp)
        {
            BBComp->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
            BBComp->SetValueAsVector(TEXT("LastKnowLocation"), PlayerPawn->GetActorLocation());
        }
        
        // MoveToActor(PlayerPawn, AdvanceRadius, true);
        // SetFocus(PlayerPawn);
    }
    else
    {
        BBComp->ClearValue(TEXT("PlayerLocation"));

        // ClearFocus(EAIFocusPriority::Gameplay);
        // StopMovement();
    } */
    
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ShooterCharacter != nullptr)
    {
        return ShooterCharacter->IsDead();
    }
    return true;
}