// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ToggleTraceNotifyState.generated.h"

class UTraceComponent;

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UToggleTraceNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UTraceComponent* GetTracaeComponent(USkeletalMeshComponent* MeshComp);

	// Override the NotifyBegin and NotifyEnd methods to toggle the trace component's attack state
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration,  const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;
};
