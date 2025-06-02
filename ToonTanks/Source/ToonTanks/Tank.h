// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATank();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//--- Not following the video cause is outdated ---
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	class USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	class UCameraComponent* CameraComp;

	UFUNCTION(BlueprintCallable)
	void MoveForward(float value);

	UFUNCTION(BlueprintCallable)
	void TankTurn(float value);

	UFUNCTION(BlueprintCallable)
	void Fire(bool value);

	UPROPERTY(EditAnywhere);
	float Speed = 10.0f;
	
	UPROPERTY(EditAnywhere);
	float TurnSpeed = 10.0f; 

private:
	APlayerController* PlayerControllerRef;
};
