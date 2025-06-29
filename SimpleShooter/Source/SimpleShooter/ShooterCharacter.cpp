// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Spirng Arm Comp
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spirng Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	//Camera Comp

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Healt = Maxhealt;
	UE_LOG(LogTemp, Display, TEXT("Healt set to MaxHealt: %f"), Healt);

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	ReduceHealt(DamageApplied);

	if(IsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AShooterCharacter::Move);
		EnhancedInput->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AShooterCharacter::Look);
		EnhancedInput->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AShooterCharacter::JumpAction);
		EnhancedInput->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AShooterCharacter::FireAction);
	}
}

void AShooterCharacter::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AShooterCharacter::Look(const FInputActionValue& value)
{
 	FVector2D LookVector = value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
    AddControllerPitchInput(LookVector.Y*-1);
}

void AShooterCharacter::JumpAction()
{
	Jump();
}

void AShooterCharacter::FireAction()
{
 UE_LOG(LogTemp, Display, TEXT("Pew"));
 Gun->PullTrigger();
}

void AShooterCharacter::ReduceHealt(float value)
{
	value = FMath::Min(Healt, value);
	Healt -= value;
	UE_LOG(LogTemp, Display, TEXT("Healt Reduce Current Healt: %f "), Healt);
}

bool AShooterCharacter::IsDead() const
{
	return Healt <= 0.f;
}