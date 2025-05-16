// Fill out your copyright notice in the Description page of Project Settings.
#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	upPosition = Location;
	SetActorLocation(Location);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation.X >= MaxX || CurrentLocation.X <= MinX )
	{
		MovementSpeed *= -1.0f;
	}
	upPosition.X += DeltaTime * MovementSpeed;
	SetActorLocation(upPosition);
	


}

