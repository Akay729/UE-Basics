// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Stats[EStats::Health]);
	
}

// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::ReduceDamage(float Amount)
{	

	float ReducedHealth = FMath::Clamp(Stats[EStats::Health] - Amount, 0.0f, Stats[EStats::MaxHealth]);
	Stats[EStats::Health] = ReducedHealth;

	if (Stats[EStats::Health] == 0.0f) 
	{
		UE_LOG(LogTemp, Display, TEXT("Raggiunto il limite di danni!"));
	}
}

void UStatsComponent::ReduceStamina(float Amount)
{
	float ReducedStamina = FMath::Clamp(Stats[EStats::Stamina] - Amount, 0.0f, Stats[EStats::MaxStamina]);
	Stats[EStats::Stamina] = ReducedStamina;
}
