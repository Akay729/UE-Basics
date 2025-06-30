// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;
class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();

private:
	//
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleParticleSystem;
	
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* BulletParticleSystem;

	UPROPERTY(EditDefaultsOnly)
	float MaxRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;
	
	FCollisionQueryParams Params;

	bool GunTrace(FHitResult& HitResult, FVector& ShotDirection);

	AController* GetOwnerController();
};
