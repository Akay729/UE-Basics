// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebughelpers.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
// Sets default values

#define ECC_Bullet ECollisionChannel::ECC_GameTraceChannel1

AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	GunMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleParticleSystem, GunMesh, TEXT("MuzzleFlashSocket"));
	//DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), 90, 1,  FColor::Green, true);

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;


	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	
	OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	FVector EndPoint = ViewPointLocation + ViewPointRotation.Vector() * MaxRange; //Questo non riuscivo a capirlo
	
	//DrawDebugCamera(GetWorld(), ViewPointLocation, ViewPointRotation, 0, 1, FColor::Red, false, 2.0f);
	//DrawDebugLine(GetWorld(), ViewPointLocation, EndPoint, FColor::Red, false, 2.0f);
	
	FHitResult HitResult;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerPawn);
	bool isHit = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPointLocation, EndPoint, ECC_Bullet, Params);
	
	if(isHit)
	{
		//DrawDebugLine(GetWorld(), ViewPointLocation, HitResult.ImpactPoint, FColor::Green, false, 2.0f);
		FVector ShotDirection = ViewPointRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletParticleSystem,  HitResult.ImpactPoint, ShotDirection.Rotation(), true);
		
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
		
	}

}
