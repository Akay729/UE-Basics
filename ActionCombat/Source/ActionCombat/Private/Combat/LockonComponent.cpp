// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	}
	
}

void ULockonComponent::StartLockOn(float SphereRadius, float Range)
{
	if (!OwnerCharacter) return;
	FHitResult HitResult;
	FVector Start = OwnerCharacter->GetActorLocation();
	FVector End = Start + OwnerCharacter->GetActorForwardVector() * Range;
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
	
	CurrentTargetActor = HitResult.GetActor();

	UE_LOG(LogTemp, Warning, TEXT("Lockon Hit: %s"), *CurrentTargetActor->GetName());
	OwnerController->SetIgnoreLookInput(true);
	OwnerMovementComponent->bOrientRotationToMovement = false;
	OwnerMovementComponent->bUseControllerDesiredRotation = true;
	
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Start, CurrentTargetActor->GetActorLocation());
	//OwnerCharacter->SetActorRotation(FRotator(0.0f, HitResult.ImpactNormal.Rotation().Yaw, 0.0f));


}

// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If we have a target, rotate towards it
	if (CurrentTargetActor != nullptr && OwnerCharacter != nullptr)
	{
		FVector TargetLocation = CurrentTargetActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), TargetLocation);
		//OwnerCharacter->SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));
		OwnerController->SetControlRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));
	}
	
}

