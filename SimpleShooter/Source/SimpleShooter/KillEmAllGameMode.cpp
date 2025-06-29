// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "ShooterPlayerController.h"
#include "EngineUtils.h"

void AKillEmAllGameMode::PawnKilled(APawn* KilledPawn)
{
    Super::PawnKilled(KilledPawn);
    UE_LOG(LogTemp, Display, TEXT("Pawn Dead"));

    APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
    if(PlayerController != nullptr)
    {
        EndGame(false);
    }
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
