// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateCurrentVelocity()
{
    APawn * OwningPawn = {TryGetPawnOwner()};
    if (!IsValid(OwningPawn)) return;
    {
        FVector Velocity = OwningPawn->GetVelocity();
        CurrentVelocity = static_cast<float>(Velocity.Length());
    }
}