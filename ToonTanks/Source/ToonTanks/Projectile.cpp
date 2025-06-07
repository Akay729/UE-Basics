// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = false; // non ha bisogno di fare tick ogni volta

	//Aggiunta che avevo fatto io
/* 	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsule"));
	RootComponent = CapsuleComp; */
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugSphere(GetWorld(), GetActorLocation(), 10, 16, FColor::Blue, false, 5.0f);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
