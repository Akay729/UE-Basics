// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/TraceComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interfaces/Enemy.h"
#include "Interfaces/Fighter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"

#define ECC_Fight ECC_GameTraceChannel1

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	SkeletalComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalComponent) return;

	Params.AddIgnoredActor(GetOwner());
	Params.TraceTag = FName(TEXT("IngoreTrace"));
	Params.bTraceComplex = false;
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsAttacking) return;
	
	TArray<FHitResult> AllResult;

	for (const FTraceSockets Socket : Sockets)
	{

			FVector StartSocketLocaiton {SkeletalComponent->GetSocketLocation(Socket.WeaponStart)};
			FVector EndSocketLocation {SkeletalComponent->GetSocketLocation(Socket.WeaponEnd)};
			FQuat ShapeRotation {SkeletalComponent->GetSocketQuaternion(Socket.Roatation)};
		
			double DistanceStartEnd = FVector::Distance(StartSocketLocaiton, EndSocketLocation);
		
			FVector BoxHalfExtent {DistanceStartEnd, BoxCollisionLength, BoxCollisionLength}; // Half-height for the box
			BoxHalfExtent *= 0.5f;
		
			FCollisionShape BoxShape = FCollisionShape::MakeBox(BoxHalfExtent);
		
			TArray<FHitResult> HitResults;
		
			bool isHit =  GetWorld()->SweepMultiByChannel(
				HitResults, 
				StartSocketLocaiton, 
				EndSocketLocation, 
				ShapeRotation, 
				ECC_Fight, 
				BoxShape, // Assuming a sphere shape for the trace
				FCollisionQueryParams::DefaultQueryParam
			);
			
			for (const FHitResult Hit : HitResults) AllResult.Add(Hit);
			//--------- NOPE ---------//
			/* if (isHit)
			{
				for (const FHitResult& Hit : HitResults)
				{
					AActor* CurrentHitActor = Hit.GetActor();
					UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *CurrentHitActor->GetName());
					if (CurrentHitActor && CurrentHitActor->Implements<UFighter>())
					{
						IFighter::Execute_GetDamage(CurrentHitActor);
						// Handle the hit actor, e.g., apply damage or log it
						//UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName());
						}
				}
				}*/
			//--------- END of NOPE ---------//	
			if (bIsDebug)
			{	
				UE_LOG(
				LogTemp, Warning, 
				TEXT("Start: %s, End: %s, Rotation: %s"), 
				*StartSocketLocaiton.ToString(), 
				*EndSocketLocation.ToString(), 
				*ShapeRotation.Rotator().ToString()); 
		
				FVector CenterPoint {
					UKismetMathLibrary::VLerp(
						StartSocketLocaiton, 
						EndSocketLocation, 
						0.5f
					)
				};
				
				UKismetSystemLibrary::DrawDebugBox(
					GetWorld(), 
					CenterPoint, 
					BoxShape.GetExtent(),
					isHit ? FColor::Green : FColor::Red,
					ShapeRotation.Rotator(),
					1.0f,
					2.0f
				);
			}
		}

		if (AllResult.Num() > 0)
		{
			float CharacterDamage {};
			IFighter* FighterInterface = Cast<IFighter>(GetOwner());
			if (FighterInterface)
			{
				CharacterDamage = FighterInterface->GetDamage();
			}
	
			FDamageEvent DamageEvent;
			//TSet<FHitResult> HitResultsSet(HitResults);
	
			for (const FHitResult& Hit : AllResult)
			{
				AActor* CurrentHitActor = Hit.GetActor();
	
				if (ActorToIgnore.Contains(CurrentHitActor)) continue;
	
				CurrentHitActor->TakeDamage(
					CharacterDamage, 
					DamageEvent, 
					GetOwner()->GetInstigatorController(), 
					GetOwner()
				);
	
				ActorToIgnore.AddUnique(CurrentHitActor);
			}
		}
	
}
	 
void UTraceComponent::HandleResetAttack()
{
	// Reset the attack state after the montage ends
	ActorToIgnore.Empty();
}