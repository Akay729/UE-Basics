// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"

class USkeletalMeshComponent;
class FCollisonQueryParams;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	USkeletalMeshComponent* SkeletalComponent;
	
	UPROPERTY(EditAnywhere)
	FName WeaponStart;

	UPROPERTY(EditAnywhere)
	FName WeaponEnd;

	UPROPERTY(EditAnywhere)
	FName Roatation;

	UPROPERTY(EditAnywhere)
	bool bIsDebug {false};

	TArray<AActor*> ActorToIgnore;

	
public:	
	// Sets default values for this component's properties
	UTraceComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	FCollisionQueryParams Params;
	
	UPROPERTY(EditAnywhere)
	float BoxCollisionLength {100.0f};
	
	
	/* 	UPROPERTY(EditAnywhere)
	float BoxCollisionWidth {50.0f}; */
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();
		
};
