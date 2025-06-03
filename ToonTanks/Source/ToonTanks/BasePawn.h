// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
/* 	// Called every frame
	virtual void Tick(float DeltaTime) override; */

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true")) // questo macro espone ciò che ha sotto ad unreal
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 VisibleAnywhereInt = 31;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EditableAnywhereInt = 32;

	UPROPERTY(VisibleInstanceOnly) //Questo viene visto solo quando viene istanziato nel world 
	int32 VisibleInstanceOnlyInt = 33;

	// Da Togliere percheè altrimenti causa shadowing
	/* UPROPERTY(EditAnywhere, BlueprintReadWrite) // var creata
	float speed;
 */
	UPROPERTY(VisibleDefaultsOnly)
	int32 VisibleDefaultsOnlyInt = 34;

	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultsOnlyInt = 36;

	UPROPERTY(EditInstanceOnly)
	int32 EditInstanceOnlyInt = 37;

};
