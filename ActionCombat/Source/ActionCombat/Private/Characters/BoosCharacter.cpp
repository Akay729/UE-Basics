// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BoosCharacter.h"
#include "Characters/StatsComponent.h"

// Sets default values
ABoosCharacter::ABoosCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Combata Component
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));


}

// Called when the game starts or when spawned
void ABoosCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoosCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoosCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// IEnemy Interface
float ABoosCharacter::GetDamage()
{
	// Implement the logic to return the damage value for this character
	return 10.0f; // Example value, replace with actual logic
}

void ABoosCharacter::DetectedPawn(APawn* PawnDetected, APawn* PawnWanted)
{
    if (PawnDetected == PawnWanted)
    {
        UE_LOG(LogTemp, Warning, TEXT("Detected Same Pawn"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Detected different Pawn: %s, Wanted: %s"), *PawnDetected->GetName(), *PawnWanted->GetName());
    }
}