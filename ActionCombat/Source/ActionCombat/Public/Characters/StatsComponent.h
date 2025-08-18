// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/EStat.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(
	FOnHealthChangeSignature,
	UStatsComponent, OnHealthChangeDelegate
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(
	FOnStaminaChangeSignature,
	UStatsComponent, OnStaminaChangeDelegate
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	double StaminaRegenRate {5.0f}; // Rate at which stamina regenerates per second

	UPROPERTY(VisibleAnywhere)
	bool bCanRegenerateStamina {true}; // Flag to control stamina regeneration

	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration {2.0f}; // Delay before stamina starts regenerating after being reduced

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStats>, float> Stats;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChangeSignature OnStaminaChangeDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ReduceDamage(float Amount);

	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float Amount);	

	UFUNCTION(BlueprintCallable)
	void RestoreStamina();

	UFUNCTION()
	void EnableRegeration();

	UFUNCTION(BlueprintPure)
	float GetStatPercentage(EStats Current, EStats Max);
};
