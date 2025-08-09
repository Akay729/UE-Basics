// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class UAnimMontage;


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature, 
	UCombatComponent, OnAttackPerformedDelegate,
	float, StaminaCostValue
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AnimMontages;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentComboIndex {0};

	UPROPERTY(EditAnywhere, Category = "Combat")
	float StaminaCost {10.0f};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bCanAttack {true};
	
	UPROPERTY(BlueprintAssignable)
	FOnAttackPerformedSignature OnAttackPerformedDelegate;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
	UPROPERTY()
	ACharacter* Owner;

	
public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ComboAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HandleResetAttck();
		
};
