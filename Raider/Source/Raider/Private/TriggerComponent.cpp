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
    TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor: Actors)
	{
		if (Actor->ActorHasTag(key))
		{
			UE_LOG(LogTemp, Display, TEXT("chiave corretta"));
			return;
		}
	}
}