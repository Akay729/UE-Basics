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

	//Check if PhysicsHandleComponent is part of the actor. 
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (HasPhysicsHandle())
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
	// SphereSweepTracer(Start, End);
	// PrintDamage(dmg);
	if (!HasPhysicsHandle()) {return;}
	UPhysicsHandleComponent* PhysicsHandle =GetPhysicsHandle();
	if( PhysicsHandle->GetGrabbedComponent()!= nullptr)
	{
		FVector TagetLocation = GetComponentLocation() + GetForwardVector() * 200.0f;
		PhysicsHandle->SetTargetLocationAndRotation(TagetLocation, GetComponentRotation());
	}	
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

void UGrabber::SphereSweepTracer(FVector StartPoint, FVector EndPoint)
{
	FHitResult HitResult;
	DrawDebugLine(GetWorld(),StartPoint,EndPoint,FColor::Green);
	bool isHit = GetWorld()->SweepSingleByChannel(HitResult, StartPoint, EndPoint, FQuat::Identity, ECC_Grabber, CollisionShape, Params, FCollisionResponseParams());
	if (isHit)
	{
		FVector Extent = FVector(5.0f, 5.0f, 5.0f);
		UE_LOG(LogTemp, Display, TEXT("SphereSweepTracer Object Hit: %s "), *HitResult.GetActor()->GetName());
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

void UGrabber::CapsuleSweepTracer(FVector StartPoint, FVector EndPoint)
{
	/*
	Questa Funzione l'ho fatta solo perchè pensavo fosse neccessario nel tutorial 
	ma siè rilevato qualcosa di molto più complesso. 
	Ero vicino alla soluzione ma non avevo capito bene cosa facesse sweep
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
		UE_LOG(LogTemp, Display, TEXT("CapsuleSweepTracer Object Hit: %s "), *HitResult.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No Hit!"));
	}
	
}

// Grab Actor
void UGrabber::Grab()
{
	// Check PhysicsHandleComponet
	if (!HasPhysicsHandle()) {return;}
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	FHitResult HitResult;
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetForwardVector()*Distance;

	bool isHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_Grabber, CollisionShape, Params, FCollisionResponseParams());

	if (isHit)
	{
		FVector Extent = FVector(2.5f, 2.5f, 2.5f);
		DrawDebugSphere(GetWorld(), HitResult.Location, Radius, 12, FColor::Red, false, 5.0f);
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, Extent, FQuat::Identity, FColor::Yellow, false, 5.0f);

		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	else
	{
		DrawDebugSphere(GetWorld(), End, Radius, 12, FColor::Blue, false, 5.0f);
		//UE_LOG(LogTemp, Display, TEXT("Grab: Nothing found"));
	}
}

// Release Actor Grabbed
void UGrabber::Release()
{
	
	if (!HasPhysicsHandle()) {return;}
	PhysicsHandle = GetPhysicsHandle();
	
	UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if (GrabbedComponent != nullptr)
	{
		GrabbedComponent->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
	UE_LOG(LogTemp, Display, TEXT("Release:"));
}

// Get Physics Handle if component is present otherwise give a warning that "PhysicsHandleComponent" is missing
UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const 
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr) { UE_LOG(LogTemp, Warning, TEXT("PhysicsHandleComponent is missing"));}
	return Result;
}

// Check if GetPhysicsHandle have a retunr a nullptr or a component
bool UGrabber::HasPhysicsHandle() const
{
	//UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	return PhysicsHandle != nullptr;
}

///////////// OLD CODE /////////////

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


// Old solution for the lesson
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