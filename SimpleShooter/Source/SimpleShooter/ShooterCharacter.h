// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

//Forward Declaration
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void JumpAction();
	void FireAction();

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Move;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_Fire;

	UPROPERTY(VisibleAnywhere, Category="Settings")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category="Settings")
	UCameraComponent* CameraComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

private:
	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
	float Maxhealt = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float Healt = 100.0f;

	void ReduceHealt(float value);
};
