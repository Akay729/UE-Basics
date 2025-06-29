// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* KilledPawn)
{
    Super::PawnKilled(KilledPawn);
    UE_LOG(LogTemp, Display, TEXT("Pawn Dead"));

    APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
    if(PlayerController != nullptr)
    {
       PlayerController->GameHasEnded(nullptr, false); 
    }
}