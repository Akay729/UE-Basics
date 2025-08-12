// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LookAtPlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULookAtPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookAtPlayerComponent();

	UPROPERTY(VisibleAnywhere)
	bool bCanRotate {false};

	UPROPERTY(EditAnywhere)
	float LookAtDistance = 2000.0f; // Distance to look at the player
	
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 200.f; 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	AActor* OwnerActor;
	
	UPROPERTY(VisibleAnywhere)
	APawn* PlayerActor;
		
};
