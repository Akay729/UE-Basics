// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


//Questo costruttore serve principalmente principalmente per attivare tick 
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("TriggerComponent"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AActor* Actor = GetAcceptableActor();
	if (Actor)
	{
		Mover->SetShouldMove(true);
		UE_LOG(LogTemp, Display, TEXT("Unlocking!"));
	}
	else
	{
		Mover->SetShouldMove(false);
		UE_LOG(LogTemp, Display, TEXT("Locking!"));
	}
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor: Actors)
	{
		if (Actor->ActorHasTag(key) && Actor->Tags.Contains("Grabbed")!=true) //2 modi per fare la stessa cosa
		{
			UE_LOG(LogTemp, Display, TEXT("chiave corretta"));
			return Actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}