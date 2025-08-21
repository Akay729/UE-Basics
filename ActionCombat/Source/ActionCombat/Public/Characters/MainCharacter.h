// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/MainPlayer.h"
#include "Interfaces/Fighter.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UPlayerAnimInstance;
class USkeletalMeshComponent;
class UCombatComponent;
class UStatsComponent;
class ULockonComponent;
class UTraceComponent;
class UBlockComponent;
class UPlayerActionsComponent;

struct FInputActionValue;


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateMainCharacter, Log, All);

UCLASS()
class ACTIONCOMBAT_API AMainCharacter : public ACharacter, public IMainPlayer, public IFighter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	/** Block Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BlockAction;

public:
	AMainCharacter();
	/** Components */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStatsComponent* StatsComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCombatComponent* CombatComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ULockonComponent* LockonComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTraceComponent* TraceComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBlockComponent* BlockComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPlayerActionsComponent* PlayerActionsComponent;

	/** Death Animation Montange */
	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnimMontage;

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

protected:

	virtual void BeginPlay() override;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Attack();
	
	void StartBlocking();
	void EndBlocking();

	/* UPROPERTY(BlueprintReadOnly)
	UCombatComponent* CombatComponent; */

	UPROPERTY(BlueprintReadOnly)
	UPlayerAnimInstance* PlayerAnimInstance;

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Fighter Interface
	virtual float GetDamage() override;
	virtual bool CanTakeDamage(AActor* Opponent) override;

	// IMainPlayer Interface
	virtual bool HasEnoughStamina(float StaminaCost) const override;
	virtual void EndLockonWithActor(AActor* Actor) override;
	
};
