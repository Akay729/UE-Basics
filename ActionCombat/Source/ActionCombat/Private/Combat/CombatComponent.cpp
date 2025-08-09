// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimMontage.h"
#include "Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner<ACharacter>();
	if (!Owner) return;
	
}

void UCombatComponent::ComboAttack()
{
	if (!bCanAttack) return;
	bCanAttack = false;

	Owner->PlayAnimMontage(AnimMontages[CurrentComboIndex]);

	CurrentComboIndex++;

	int MaxCombo{ AnimMontages.Num() };

	CurrentComboIndex = UKismetMathLibrary::Wrap(
		CurrentComboIndex,
		-1,
		(MaxCombo - 1)
	);

	OnAttackPerformedDelegate.Broadcast(StaminaCost);
}

void UCombatComponent::HandleResetAttck()
{
	// Reset the attack state after the montage ends
	bCanAttack = true;
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

