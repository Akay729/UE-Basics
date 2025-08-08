// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/TraceComponent.h"
#include "Components/SkeletalMeshComponent.h"

#define ECC_Fight ECC_GameTraceChannel1

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	SkeletalComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalComponent) return;

	Params.AddIgnoredActor(GetOwner());
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector StartSocketLocaiton {SkeletalComponent->GetSocketLocation(WeaponStart)};
	FVector EndSocketLocation {SkeletalComponent->GetSocketLocation(WeaponEnd)};
	FQuat ShapeRotation {SkeletalComponent->GetSocketQuaternion(Roatation)};

	TArray<FHitResult> HitResults;

	bool isHit =  GetWorld()->SweepMultiByChannel(
		HitResults, 
		StartSocketLocaiton, 
		EndSocketLocation, 
		ShapeRotation, 
		ECC_Fight, 
		FCollisionShape::MakeSphere(50.0f), // Assuming a sphere shape for the trace
		FCollisionQueryParams::DefaultQueryParam
	)

	UE_LOG(
		LogTemp, Warning, 
		TEXT("Start: %s, End: %s, Rotation: %s"), 
		*StartSocketLocaiton.ToString(), 
		*EndSocketLocation.ToString(), 
		*ShapeRotation.Rotator().ToString());
}

