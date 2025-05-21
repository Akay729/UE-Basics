// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetForwardVector()*Distance;

/* 	FRotator ComponertRotation = GetComponentRotation();
	FVector Forward = ComponentRotation.Vector();
	End += Forward * 100;  */


	DrawDebugLine(GetWorld(),Start,End,FColor::Green);




/* 	FRotator CurrentRotation = GetComponentRotation();
	UWorld* World = GetWorld();
	if(World)
	{

		now = World->TimeSeconds();
		//now = World->GetTimeSeconds(); //Sono la stessa funzione
		
		bool = World->LineTraceSingleByChannel(s,e);

	}
	double now = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Display, TEXT("Rotation: %s"), *CurrentRotation.ToString());
	UE_LOG(LogTemp, Display, TEXT("Time: %.5f"), now); */
}

