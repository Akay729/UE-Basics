// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true; // non ha bisogno di fare tick ogni volta

	//Aggiunta che avevo fatto io
/* 	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsule"));
	RootComponent = CapsuleComp; */
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = MeshComp;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Move Comp"));
	ProjectileMovementComp->MaxSpeed = 1000.0f;
	ProjectileMovementComp->InitialSpeed = 1000.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormaImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit Hit Component: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OnHit Other Actor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OnHit Other Component: %s"), *OtherComp->GetName());
		
}
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

