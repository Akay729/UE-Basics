// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/HitResult.h"
#include "CollisionShape.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


//Questo lo si puo determinare dalo file DefaultEngine.ini nella cartella config
#define ECC_Grabber ECollisionChannel::ECC_GameTraceChannel2

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Params.AddIgnoredActor(GetOwner());
	IgnoredActors.Add(GetOwner()); 
	CollisionShape = FCollisionShape::MakeSphere(Radius);
	TraceColor = FLinearColor::Green;

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("nome: %s"), *PhysicsHandle->GetName() );
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("PhysicsHandleComponent is missing"));
	}
	
	

	
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// FVector Start = GetOwner()->GetActorLocation();
	// FVector End = Start + GetForwardVector()*Distance;
	// SweepTracer(Start, End);
	
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {return;}

	FVector TagetLocation = GetComponentLocation() + GetForwardVector() * 200.0f;
	PhysicsHandle->SetTargetLocationAndRotation(TagetLocation, GetComponentRotation());
	//PrintDamage(dmg);



}

// Metodo che riceve il danno come copia (non modifica il valore originale)
void UGrabber::PrintDamagePlusFive_ByValue(float Damage)
{
	FString ActorName = GetOwner()->GetActorNameOrLabel();
	Damage += 5;
	UE_LOG(LogTemp, Display, TEXT("Actor: %s | Damage (copy): %f"), *ActorName, Damage);
}

// Metodo che riceve il danno per riferimento (modifica il valore originale)
void UGrabber::PrintDamagePlusFive_ByReference(float& Damage)
{
	FString ActorName = GetOwner()->GetActorNameOrLabel();
	Damage += 5;
	UE_LOG(LogTemp, Display, TEXT("Actor: %s | Damage (ref): %f"), *ActorName, Damage);
}

void UGrabber::LineTracer(FVector StartPoint, FVector EndPoint)
{
	FHitResult HitResult;
	DrawDebugLine(GetWorld(),StartPoint,EndPoint,FColor::Green);
	bool isHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Grabber,	Params, FCollisionResponseParams());
	if (isHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Object Hit: %s (LineTracer)!"), *HitResult.GetActor()->GetName());
	}
}

void UGrabber::SweepTracer(FVector StartPoint, FVector EndPoint)
{
	FHitResult HitResult;
	DrawDebugLine(GetWorld(),StartPoint,EndPoint,FColor::Green);
	bool isHit = GetWorld()->SweepSingleByChannel(HitResult, StartPoint, EndPoint, FQuat::Identity, ECC_Grabber, CollisionShape, Params, FCollisionResponseParams());
	if (isHit)
	{
		FVector Extent = FVector(5.0f, 5.0f, 5.0f);
		UE_LOG(LogTemp, Display, TEXT("Object Hit: %s (SweepTracer 1)!"), *HitResult.GetActor()->GetName());
		DrawDebugSphere(GetWorld(), HitResult.Location, Radius, 16, FColor::Yellow, false, 0.0f);
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, Extent, FQuat::Identity, FColor::Yellow, false, 0.0f);
		//DrawDebugSphere(GetWorld(), EndPoint, Radius, 16, FColor::Green, false, 0.0f);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit!"));
		DrawDebugSphere(GetWorld(), EndPoint, Radius, 16, FColor::Green, false);
	}
}

void UGrabber::SweepTracer2(FVector StartPoint, FVector EndPoint)
{
	/*
	Questa Funzione l'ho fatta solo perchè pensavo fosse neccessario nel tutorial 
	ma siè rilevato qualcosa di molto più complesso, poco uso di ai e solo per banalita o cercare definizioni.
	*/

	FHitResult HitResult;
	//CollisionShape.MakeCapsule(Radius, HalfHeight);
	FRotator ComponertRotation = GetComponentRotation();
	//const FQuat OrientationQuat = ComponertRotation.Quaternion();
	

 	UKismetSystemLibrary::CapsuleTraceSingle(
		GetWorld(),
		StartPoint,
		EndPoint,
		Radius,
		HalfHeight,
		UEngineTypes::ConvertToTraceType(ECC_Grabber),
		false,
		IgnoredActors,
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true,
		FLinearColor::Green,                    // Trace color
    	FLinearColor::Red,                      // Hit color
    	1.0f
	);
	//UKismetSystemLibrary::DrawDebugCapsule(GetWorld(), StartPoint, HalfHeight, Radius, ComponertRotation, TraceColor.ToFColor(true), false, 0.f);
	DrawDebugLine(GetWorld(),StartPoint,EndPoint,FColor::Red);
	//DrawDebugCapsule(GetWorld(), StartPoint, HalfHeight, Radius, ComponertRotation.Quaternion(), FColor::Green);

	
	// per indicare no rotation si usa FQuat::Identity
	bool isHit = GetWorld()->SweepSingleByChannel(HitResult, StartPoint, EndPoint,FQuat::Identity, ECC_Grabber, CollisionShape, Params, FCollisionResponseParams());	// per indicare no rotation si usa FQuat::Identity
	
	if (isHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Object Hit: %s (SweepTracer 2)!"), *HitResult.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit!"));
	}
	
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {return;}

	FHitResult HitResult;
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetForwardVector()*Distance;

	bool isHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_Grabber,
		CollisionShape,
		Params,
		FCollisionResponseParams()
	);

	if (isHit)
	{
		FVector Extent = FVector(2.5f, 2.5f, 2.5f);
		DrawDebugSphere(GetWorld(), HitResult.Location, Radius, 12, FColor::Red, false, 5.0f);
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, Extent, FQuat::Identity, FColor::Yellow, false, 5.0f);

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	else
	{
		DrawDebugSphere(GetWorld(), End, Radius, 12, FColor::Blue, false, 5.0f);
	}
	
	
	//UE_LOG(LogTemp, Display, TEXT("Grab: Nothing found"));
}
void UGrabber::Release()
{

	//UPhysicsHandleComponent::ReleaseComponent();
	UE_LOG(LogTemp, Display, TEXT("Release"));
}

void UGrabber::OldSolution()
{
/* 	FRotator ComponertRotation = GetComponentRotation();
	FVector Forward = ComponentRotation.Vector();
	End += Forward * 100;  */
/* 	FRotator CurrentRotation = GetComponentRotation();
	UWorld* World = GetWorld();
	if(World)
	{

		now = World->TimeSeconds();
		//now = World->GetTimeSeconds(); //Sono la stessa funzione
		
		bool = World->LineTraceSingleByChannel(s,e);

	}
	double now = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Display, TEXT("Rotation: %s"), *CurrentRotation.ToString());
	UE_LOG(LogTemp, Display, TEXT("Time: %.5f"), now); */
}