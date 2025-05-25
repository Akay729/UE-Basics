// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CollisionQueryParams.h"
#include "CollisionShape.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void Grab();
	UFUNCTION(BlueprintCallable)
	void Release();

private:
	double now;
	float dmg = 5;
	FCollisionQueryParams Params;
	TArray<AActor*> IgnoredActors;
	FCollisionShape CollisionShape;
	FLinearColor TraceColor;
	//FCollisionShape CollisionShape;

	UPROPERTY(EditAnywhere)
	float Distance = 500;

	UPROPERTY(EditAnywhere)
	float Radius = 50;

	UPROPERTY(EditAnywhere)
	float HalfHeight = 100;

	void PrintDamagePlusFive_ByValue(float Damage);
	void PrintDamagePlusFive_ByReference(float& Damage);
	void PrintDamage_ByReference(const float& Damage); //usando const la varibile non viene cambiata e deve essere di tipo const
	
	void LineTracer(FVector StartPoint, FVector EndPoint);
	void SphereSweepTracer(FVector StartPoint, FVector EndPoint);
	void CapsuleSweepTracer(FVector StartPoint, FVector EndPoint);
	bool HasPhysicsHandle() const;
	UPhysicsHandleComponent* GetPhysicsHandle() const;
	bool GetGrabbableInReach(FHitResult& OutHitResult);
	
	void OldSolution();
};
