// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetAnimationLibrary.h"


void UPlayerAnimInstance::UpdateCurrentSpeed()
{
    APawn * OwningPawn = {TryGetPawnOwner()};
    if (!IsValid(OwningPawn)) return;
    {
        FVector Velocity = OwningPawn->GetVelocity();
        CurrentSpeed = static_cast<float>(Velocity.Length());
    }
}
void UPlayerAnimInstance::HandleUpdateTarget(AActor *TargetActor)
{
    bIsInCombat = IsValid(TargetActor);
}

void UPlayerAnimInstance::UpdateDirection()
{
    APawn* PawnRef {TryGetPawnOwner()};
    if (!IsValid(PawnRef)) return;

    if(!bIsInCombat) return;

    // need to be replaced with UKismetAnimationLibrary::CalculateDirection
    CurrentDirection = UKismetAnimationLibrary::CalculateDirection(PawnRef->GetVelocity(), PawnRef->GetActorRotation());
}