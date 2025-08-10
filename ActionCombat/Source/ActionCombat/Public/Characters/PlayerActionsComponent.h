// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature, 
	UPlayerActionsComponent, OnSprintDelegate,
	float, StaminaCostValue
);

class UCharacterMovementComponent;
class IMainPlayer;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerCharacter;

	IMainPlayer* MainPlayerInterface;

	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(EditAnywhere, Category = "Player Actions")
	float DefaultWalkSpeed {500.0f};

	UPROPERTY(EditAnywhere, Category = "Player Actions")
	float SprintWalkSpeed {800.0f};

	UPROPERTY(EditAnywhere, Category = "Player Actions")
	float SprintStaminaCost {0.1f};
	
public:	
	// Sets default values for this component's properties
	UPlayerActionsComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate; 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Sprint();
	
	UFUNCTION(BlueprintCallable)
	void Walk();
};
