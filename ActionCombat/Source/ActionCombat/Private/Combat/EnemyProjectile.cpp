// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/EnemyProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyProjectile::HandleBeginOverlap(AActor* OtherActor)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if(!OtherPawn->IsPlayerControlled()) return;

	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);
	
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();

	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FDamageEvent DamageEvent;
	OtherPawn->TakeDamage(
		FireballDamage,
		DamageEvent,
		OtherPawn->GetController(),
		this
	);


	GetWorldTimerManager().SetTimer(
		DestoryProjectileTimerHandler,
		this,
		&AEnemyProjectile::DestroyProjectile,
		0.5f
	);

}

void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}
