// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Tower.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimeHandler, this, &ATower::TowerBehavour, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Tank)
    {
        FVector TargetLocation =  Tank->GetActorLocation();
        float Distance = FVector::Dist(GetActorLocation(), TargetLocation);//Distance to the tank
        if (Distance <= FireRange)//Check if tank is in range
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

void ATower::TowerBehavour()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());//Distance to the tank
        if (Distance <= FireRange)
        {
            Fire();
        }
    }
}