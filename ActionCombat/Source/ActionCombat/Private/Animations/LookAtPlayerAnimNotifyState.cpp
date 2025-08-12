// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/LookAtPlayerAnimNotifyState.h"
#include "Characters/LookAtPlayerComponent.h"

void ULookAtPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    ULookAtPlayerComponent* RotationComp{GetRotationComp(MeshComp)};
    if (!IsValid(RotationComp)) return;

    RotationComp->bCanRotate = true;
}
void ULookAtPlayerAnimNotifyState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    ULookAtPlayerComponent* RotationComp{GetRotationComp(MeshComp)};
    if (!IsValid(RotationComp)) return;
    
    RotationComp->bCanRotate = false;
}

ULookAtPlayerComponent *ULookAtPlayerAnimNotifyState::GetRotationComp(USkeletalMeshComponent *MeshComp)
{
    AActor* OwnerActor {MeshComp->GetOwner()};
    if (!IsValid(OwnerActor)) return nullptr;

    ULookAtPlayerComponent* RotationComp{OwnerActor->FindComponentByClass<ULookAtPlayerComponent>()};
    if (!IsValid(RotationComp)) return nullptr;
    return RotationComp;
}