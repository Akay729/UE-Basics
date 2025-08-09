// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Interfaces/Fighter.h"
#include "BoosCharacter.generated.h"

class UStatsComponent;

UCLASS()
class ACTIONCOMBAT_API ABoosCharacter : public ACharacter, public IEnemy, public IFighter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoosCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	UStatsComponent* StatsComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IEnemy Interface
	virtual float GetDamage() override;

};
