// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	MyFloat = 29;
	OriginalLocation = GetOwner()->GetActorLocation();	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DoorMovemnt(ShouldMove, DeltaTime);
}

void  UMover::DoorMovemnt(bool ShouldOpen, float DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation;

	if (ShouldOpen)
	{
		TargetLocation = OriginalLocation + MoveOffset;
	}
	else
	{
		TargetLocation = OriginalLocation;  // Ritorna alla posizione originale
	}

	// Log utile
	UE_LOG(LogTemp, Display, TEXT("Actor TargetLocation %s"), *TargetLocation.ToString());

	// Interpolazione costante verso il target
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 100);
	GetOwner()->SetActorLocation(NewLocation);
}

void  UMover::DoorMovemnt2(bool ShouldOpen, float DeltaTime)
{
	
	UE_LOG(LogTemp, Display, TEXT("Actor OriginalLocation %s"), *OriginalLocation.ToString());
	if (ShouldOpen)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		UE_LOG(LogTemp, Display, TEXT("Actor TargetLocation %s"), *TargetLocation.ToString());
		// float Speed = FVector::Distance(CurrentLocation, TargetLocation)/TimeToMove;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 100);
		GetOwner()->SetActorLocation(NewLocation);
	}else
	{

	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

void UMover::OldSolution()
{
	/* 	AActor* Owner = GetOwner();
	FString name = Owner->GetActorNameOrLabel();
	FVector CurrentLocation = Owner->GetActorLocation();

	float* MyFloatPointer = &MyFloat;

	UE_LOG(LogTemp, Display, TEXT("Mover Owner: %s Location %s "), *name, *CurrentLocation.ToString());

	UE_LOG(LogTemp, Display, TEXT("Componet pointer: %p "), Owner);
	UE_LOG(LogTemp, Display, TEXT("Componet address: %p "), &Owner);
	UE_LOG(LogTemp, Display, TEXT("Current Locaiton: %s "), *CurrentLocation.ToString());
	UE_LOG(LogTemp, Display, TEXT("Componet address: %s "), *name); // *name è un scorciatoia per ottenere Fstring in TCHAR*
	 */
}