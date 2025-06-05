// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Tank)
    {
        FVector TargetLocation =  Tank->GetActorLocation();
         //Distance to the tank
        float Distance = FVector::Dist(GetActorLocation(), TargetLocation);
        //Check if tank is in range
        if (Distance <= FireRange)
        {
            //If yes Rotatte.
            DrawDebugSphere(GetWorld(), GetActorLocation(), FireRange, 16, FColor::Green, false, 0.1f);
            RotateTurret(TargetLocation);
        }
        else
        {
            DrawDebugSphere(GetWorld(), GetActorLocation(), FireRange, 16, FColor::Red, false, 0.1f);
        }
    }    
}
