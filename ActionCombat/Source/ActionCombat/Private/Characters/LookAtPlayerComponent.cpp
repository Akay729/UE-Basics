// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LookAtPlayerComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULookAtPlayerComponent::ULookAtPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner();
	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void ULookAtPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/* FRotator* OwnerLocaiton = OwnerActor->GetActorRotation();
	FRotator* PlayerLocation = PlayerActor->GetActorRotation(); */

	if (!bCanRotate)return;

	if (IsValid(OwnerActor) && IsValid(PlayerActor))
	{
		FVector OwnerLocation = OwnerActor->GetActorLocation();
		FVector PlayerLocation = PlayerActor->GetActorLocation();

		FRotator OwnerCurrentRotation = OwnerActor->GetActorRotation();

		if (FVector::Dist(OwnerLocation, PlayerLocation) > LookAtDistance) return;
		FRotator DesiredRotation = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, PlayerLocation);

		FRotator NewRotation = UKismetMathLibrary::RInterpTo_Constant(
			OwnerCurrentRotation, DesiredRotation, DeltaTime, RotationSpeed);

		FRotator NewYawOnlyRotation {OwnerCurrentRotation.Pitch, NewRotation.Yaw, OwnerCurrentRotation.Roll};

		OwnerActor->SetActorRotation(NewYawOnlyRotation);
	}
}

