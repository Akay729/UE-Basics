// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"

class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerCharacter;
	APlayerController* OwnerController;
	UCharacterMovementComponent* OwnerMovementComponent;

public:	
	// Sets default values for this component's properties
	ULockonComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartLockOn(float SphereRadius = 100.0f, float Range = 1000.0f);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "Lockon")
	AActor* CurrentTargetActor;
	
private:

	FCollisionQueryParams Params;	
};
