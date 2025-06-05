// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/HitResult.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //Sping Arm
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(RootComponent);
    //Camera
    CameraComp =  CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    if (PlayerControllerRef)
    {
        Super::Tick(DeltaTime);
        FHitResult OutHitResult;
        bool isHit = PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHitResult);
        if (isHit)
        {
            FVector MousePoint = OutHitResult.ImpactPoint;
            DrawDebugSphere(GetWorld(),MousePoint, 10, 16, FColor::Red);
            RotateTurret(MousePoint);
            UE_LOG(LogTemp, Display, TEXT("Mouse cordinate: %s"), *OutHitResult.ImpactPoint.ToString());
        } 
    }
}

//--- Not following the video cause is outdated ---
// Called to bind functionality to input
/* void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);

} */

void ATank::MoveForward(float value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaLocation.X  = value * DeltaTime * Speed;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::TankTurn(float value)
{
    //GetWorld()->GetDeltaSeconds() // Fa la stessa cosa senza passare da una libreria utiliti
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FRotator DeltaRotation = FRotator(0.0f, value * DeltaTime * TurnSpeed, 0.0f);
    
    //DeltaRotation.yam = value;
    AddActorLocalRotation(DeltaRotation);
}

void ATank::Fire(bool value)
{
    UE_LOG(LogTemp, Display, TEXT("Shoting"));
}