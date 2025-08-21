// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Enemy.h"

#define ECC_Fight ECC_GameTraceChannel1

// Sets default values for this component's properties
ULockonComponent::ULockonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize the owner components
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		OwnerController = Cast<APlayerController>(OwnerCharacter->GetController());
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
		CameraBoom = OwnerCharacter->FindComponentByClass<USpringArmComponent>();
	}
	
}

// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If we have a target, rotate towards it
	if (CurrentTargetActor != nullptr && OwnerCharacter != nullptr)
	{
		FVector CurrentLocation = OwnerCharacter->GetActorLocation();
		FVector TargetLocation = CurrentTargetActor->GetActorLocation();
		double DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

		if( DistanceToTarget > BreakDistance)
		{
			EndLockon();
			return;
		}
		
		TargetLocation.Z -= 125.0f; // Adjust height to look at the target's head

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);

		//OwnerCharacter->SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));
		OwnerController->SetControlRotation(LookAtRotation);


	}
	
}


void ULockonComponent::StartLockOn(float SphereRadius, float SweepRange)
{
	if (!OwnerCharacter) return;
	FHitResult HitResult;
	FVector Start = OwnerCharacter->GetActorLocation();
	FVector End = Start + OwnerCharacter->GetActorForwardVector() * SweepRange;
	FCollisionShape Sphere {FCollisionShape::MakeSphere(SphereRadius)};
	Params.AddIgnoredActor(OwnerCharacter);
	Params.TraceTag = FName(TEXT("LockonTrace"));
	Params.bTraceComplex = false;

	bool isHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_Fight,
		Sphere,
		Params
	);

	if (!isHit) return;
	if (!HitResult.GetActor()->Implements<UEnemy>()) return;
	
	CurrentTargetActor = HitResult.GetActor();

	OwnerController->SetIgnoreLookInput(true);
	OwnerMovementComponent->bOrientRotationToMovement = false;
	OwnerMovementComponent->bUseControllerDesiredRotation = true;
	
	CameraBoom->TargetOffset = FVector(0.0f, 0.0f, 100.0f);
	//OwnerCharacter->SetActorRotation(FRotator(0.0f, HitResult.ImpactNormal.Rotation().Yaw, 0.0f));

	//Show Lockon Widget or any other visual feedback here
	IEnemy::Execute_OnSelect(CurrentTargetActor);
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);

	UE_LOG(LogTemp, Warning, TEXT("Lockon Hit: %s"), *CurrentTargetActor->GetName());


}

void ULockonComponent::EndLockon()
{
	if(!OwnerCharacter) return;
	// Reset the lock-on state
	UE_LOG(LogTemp, Warning, TEXT("Lockon Ended: %s"), *CurrentTargetActor->GetName());

	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	
	CurrentTargetActor = nullptr;
	OwnerController->SetIgnoreLookInput(false);
	OwnerMovementComponent->bOrientRotationToMovement = true;
	OwnerMovementComponent->bUseControllerDesiredRotation = false;
	CameraBoom->TargetOffset = FVector::ZeroVector;
	OwnerController->ResetIgnoreLookInput(); 

	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::ToggleLockOn(float SphereRadius, float SweepRange)
{
	if (CurrentTargetActor)
	{
		EndLockon();
	}
	else
	{
		StartLockOn(SphereRadius, SweepRange);
	}
}
