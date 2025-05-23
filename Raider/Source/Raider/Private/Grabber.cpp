// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "Engine/HitResult.h"
#include "CollisionShape.h"
#include "Kismet/KismetSystemLibrary.h"

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
	
	
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetOwner()->GetActorLocation();
	//FRotator Rot= GetOwner()->GetActorRotation(); 
	FVector End = Start + GetForwardVector()*Distance;
	SweepTracer(Start, End);
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
	bool isHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartPoint,
		EndPoint,
		ECC_Grabber,
		Params, 
		FCollisionResponseParams());
	
	if (isHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Object Hit: %s (LineTracer)!"), *HitResult.GetActor()->GetName());
	}
}

void UGrabber::SweepTracer(FVector StartPoint, FVector EndPoint)
{
	/*
	Questa Funzione l'ho fatta solo perchè pensavo fosse neccessario nel tutorial 
	ma siè rilevato qualcosa di molto più complesso, poco uso di ai e solo per banalita o cercare definizioni.
	*/

	FHitResult HitResult;
	FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(Radius, HalfHeight);
	//CollisionShape.MakeCapsule(Radius, HalfHeight);
	FRotator ComponertRotation = GetComponentRotation();

	DrawDebugLine(GetWorld(),StartPoint,EndPoint,FColor::Red);
	DrawDebugCapsule(GetWorld(), StartPoint, HalfHeight, Radius, ComponertRotation.Quaternion(), FColor::Green);
	
	
	// per indicare no rotation si usa FQuat::Identity
	bool isHit = GetWorld()->SweepSingleByChannel(HitResult, StartPoint, EndPoint,FQuat::Identity, ECC_Grabber, CollisionShape, Params, FCollisionResponseParams());	// per indicare no rotation si usa FQuat::Identity
	
	if (isHit)
	{
		UE_LOG(LogTemp, Display, TEXT("Object Hit: %s (SweepTracer)!"), *HitResult.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Nothing!"));
	}
	
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