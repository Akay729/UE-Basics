// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BoosCharacter.h"
#include "Characters/StatsComponent.h"
#include "Characters/EStat.h"
#include "Combat/EnemyProjectileComponent.h"
#include "Combat/TraceComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/LookAtPlayerComponent.h"
#include "AIController.h"

// Sets default values
ABoosCharacter::ABoosCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Combata Component
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	EnemyProjectileComponent = CreateDefaultSubobject<UEnemyProjectileComponent>(TEXT("EnemyProjectileComponent"));
	LookAtPlayerComponent = CreateDefaultSubobject<ULookAtPlayerComponent>(TEXT("LookAtPlayerComponent"));
	TraceComponent = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComponent"));

}

// Called when the game starts or when spawned
void ABoosCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController) return;

	BlackboardComponent = AIController->GetBlackboardComponent();
	if(!IsValid(BlackboardComponent)) return; //Throw me errors :(
	
	BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), InitialState);
}

// Called every frame
void ABoosCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoosCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// IEnemy Interface
float ABoosCharacter::GetDamage()
{
	// Implement the logic to return the damage value for this character
	return StatsComponent->Stats[EStats::Strength]; // Example value, replace with actual logic
}

void ABoosCharacter::DetectedPawn(APawn* PawnDetected, APawn* PawnWanted)
{
	if(!IsValid(BlackboardComponent)) return;
	EEnemyState CurrentState = static_cast<EEnemyState>(BlackboardComponent->GetValueAsEnum(TEXT("CurrentState")));

    if (PawnDetected != PawnWanted || CurrentState != EEnemyState::Idle) return;
	UE_LOG(LogTemp, Warning, TEXT("Detected Same Pawn"));
	BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), EEnemyState::Range);
}