// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root")); // è una funztione di default CreateDefaultSubobject bisogna passarli una classe ed il nome
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDestruction()
{
	//TODO:VFX/SFX
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation(), true);
	}
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	}
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator( 0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this), 
			20.0f
		)
	);
}

void ABasePawn::Fire()
{
    //UE_LOG(LogTemp, Display, TEXT("Shoting"));
    FVector ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
    /* UE_LOG(LogTemp, Display, TEXT("Shoting at: %s"), *ProjectileSpawnLocation.ToString());
    DrawDebugSphere(GetWorld(), ProjectileSpawnLocation, 10, 16, FColor::Red, false, 5.0f); */
    FRotator SpawnRotation = TurretMesh->GetComponentRotation();

	//auto lascia al compilere il tipo di classe
	auto Projectil = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, SpawnRotation);
	Projectil->SetOwner(this);
}

/* // Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
} */

// Called every frame
/* void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

} */
