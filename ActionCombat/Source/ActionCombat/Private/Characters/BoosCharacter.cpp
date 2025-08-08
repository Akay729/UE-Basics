// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BoosCharacter.h"

// Sets default values
ABoosCharacter::ABoosCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoosCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

