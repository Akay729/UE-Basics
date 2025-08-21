// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"

//Questa implementazione è memory efficent e non richiede l'uso di un array per memorizzare i target
//Inoltre, permette di avere un solo target alla volta, evitando la complessità di gestire più target
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdateTargetSignature, //nome del delegato
	ULockonComponent, OnUpdatedTargetDelegate, //nome della classe che emette l'evento
	AActor*, NewTargetActor //parametro dell'evento
);

class UCharacterMovementComponent;
class USpringArmComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerCharacter;
	APlayerController* OwnerController;
	UCharacterMovementComponent* OwnerMovementComponent;

	USpringArmComponent* CameraBoom;

public:	
	// Sets default values for this component's properties
	ULockonComponent();
	
	UFUNCTION(BlueprintCallable)
	void EndLockon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartLockOn(float SphereRadius = 100.0f, float Range = 1000.0f);

	UFUNCTION(BlueprintCallable)
	void ToggleLockOn(float SphereRadius = 100.0f, float Range = 1000.0f);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "Lockon")
	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintAssignable, Category = "Lockon")
	FOnUpdateTargetSignature OnUpdatedTargetDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lockon")
	double BreakDistance {1000.0f};

private:

	FCollisionQueryParams Params;	
};
