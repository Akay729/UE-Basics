// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLE_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	FVector upPosition; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	FVector Location = FVector(4800, -13000, 900);

	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 100;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MaxX = 5200.0f;
	UPROPERTY(EditAnywhere, Category="Movement")
	float MinX = 4700.0f;
};
