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

public:	
	// Sets default values for this component's properties
	UTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FCollisonQueryParams Params;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
