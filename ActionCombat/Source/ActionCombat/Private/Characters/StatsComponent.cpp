// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/StatsComponent.h"
#include "kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Fighter.h"

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

void UStatsComponent::ReduceHealth(float Amount, AActor* Opponent)
{	
	IFighter* FighterRef {GetOwner<IFighter>()};
	if (!FighterRef->CanTakeDamage(Opponent)) return;
	

	float ReducedHealth = FMath::Clamp(Stats[EStats::Health] - Amount, 0.0f, Stats[EStats::MaxHealth]);
	Stats[EStats::Health] = ReducedHealth;
	OnHealthChangeDelegate.Broadcast(GetStatPercentage(EStats::Health, EStats::MaxHealth));

	if (Stats[EStats::Health] == 0) 
	{
		OnHealthZeroDelegate.Broadcast();
		UE_LOG(LogTemp, Display, TEXT("Raggiunto il limite di danni!"));
	}
}

void UStatsComponent::ReduceStamina(float Amount)
{
	float ReducedStamina = FMath::Clamp(Stats[EStats::Stamina] - Amount, 0.0f, Stats[EStats::MaxStamina]);
	Stats[EStats::Stamina] = ReducedStamina;

	bCanRegenerateStamina = false;
	
	OnStaminaChangeDelegate.Broadcast(GetStatPercentage(EStats::Stamina, EStats::MaxStamina));

	FLatentActionInfo LatentInfo
	{
		0,
		100,
		TEXT("EnableRegeration"), //Questo è il nome della funzione che verrà chiamata dopo il delay
		this
	};

	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(),
		StaminaDelayDuration,
		LatentInfo
	);
}

void UStatsComponent::RestoreStamina()
{
	if (!bCanRegenerateStamina) return;
	
	Stats[EStats::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStats::Stamina], 
		Stats[EStats::MaxStamina], 
		GetWorld()->GetDeltaSeconds(), 
		StaminaRegenRate // Interpolation speed
	);
	OnStaminaChangeDelegate.Broadcast(GetStatPercentage(EStats::Stamina, EStats::MaxStamina));
}


//Funzione che viene chiamata dopo il delay per abilitare la rigenerazione della stamina
void UStatsComponent::EnableRegeration()
{
	bCanRegenerateStamina = true;
}
float UStatsComponent::GetStatPercentage(EStats Current, EStats Max)
{
return Stats[Current]/ Stats[Max];
}