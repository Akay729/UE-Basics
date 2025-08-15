// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_RangeAttack.generated.h"


class UAnimMontage;

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UBTT_RangeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Rage Attack")
	UAnimMontage* RangeAttackMontage;

	double Threshold{0.9};

	UPROPERTY(EditAnywhere)
	float MeleeRange {110.f};

public:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
