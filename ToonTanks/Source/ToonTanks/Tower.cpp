// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Tower.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorldTimerManager().SetTimer(FireRateTimeHandler, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (IsInFireRange())
    {
        DrawDebugSphere(GetWorld(), GetActorLocation(), FireRange, 16, FColor::Green, false, 0.1f);
        RotateTurret(Tank->GetActorLocation());//If yes Rotatte.
    }
    else
    {
        DrawDebugSphere(GetWorld(), GetActorLocation(), FireRange, 16, FColor::Red, false, 0.1f); 
    }
}

bool ATower::IsInFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());//Distance to the tank
        if (Distance <= FireRange) {return true;}//Check if tank is in range
        return false;
    }
    return false;
}

void ATower::CheckFireCondition()
{
    if(IsInFireRange()){Fire();}
}