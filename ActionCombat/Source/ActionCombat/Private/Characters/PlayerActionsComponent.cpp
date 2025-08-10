// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/PlayerActionsComponent.h"
#include "Interfaces/MainPlayer.h"

// Sets default values for this component's properties
UPlayerActionsComponent::UPlayerActionsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = GetOwner<ACharacter>();
	if (!OwnerCharacter) return;

	// Get the MainPlayer interface
	if (!OwnerCharacter->Implements<UMainPlayer>()) return;
	MainPlayerInterface = Cast<IMainPlayer>(OwnerCharacter);
	

	CharacterMovement = OwnerCharacter->FindComponentByClass<UCharacterMovementComponent>();
	if (!CharacterMovement) return;


	// ...
	
}


// Called every frame
void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerActionsComponent::Sprint()
{
	if (!MainPlayerInterface->HasEnoughStamina(SprintStaminaCost)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough stamina to sprint!"));
		Walk();
		return;
	}

	if (CharacterMovement->Velocity.Equals(FVector::ZeroVector, 1.f)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot sprint while not moving!"));
		return;
	}


	
	CharacterMovement->MaxWalkSpeed = SprintWalkSpeed;

	OnSprintDelegate.Broadcast(SprintStaminaCost);
	//OwnerCharacter->StatsComponent->ReduceStamina(SprintStaminaCost);

}

void UPlayerActionsComponent::Walk()
{
	CharacterMovement->MaxWalkSpeed = DefaultWalkSpeed;
}