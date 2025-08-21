// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Interfaces/Fighter.h"
#include "Characters/EEnemyState.h"
#include "BoosCharacter.generated.h"

class UStatsComponent;
class UBlackboardComponent;
class UEnemyProjectileComponent;
class ULookAtPlayerComponent;
class UTraceComponent;
class UCombatComponent;
class AAIController;

UCLASS()
class ACTIONCOMBAT_API ABoosCharacter : public ACharacter, public IEnemy, public IFighter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnimMontage;

	AAIController* AIController;

public:
	// Sets default values for this character's properties
	ABoosCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	UStatsComponent* StatsComponent;
	
	UPROPERTY(BlueprintReadOnly)
	UEnemyProjectileComponent* EnemyProjectileComponent;

	UPROPERTY(BlueprintReadOnly)
	ULookAtPlayerComponent* LookAtPlayerComponent;

	UPROPERTY(EditAnywhere)
	UCombatComponent* CombatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTraceComponent* TraceComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DetectedPawn(APawn* PawnDetected, APawn* PawnWanted);

	UFUNCTION(BlueprintCallable)
	void HandlePlayerDeath();

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

	// IEnemy Interface
	virtual float GetDamage() override;

	virtual void Attack() override;

	virtual float GetAnimDuration() override;

	void FinishDeathAnimation();

};
