// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTraceSockets.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ACTIONCOMBAT_API FTraceSockets
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName WeaponStart;

	UPROPERTY(EditAnywhere)
	FName WeaponEnd;

	UPROPERTY(EditAnywhere)
	FName Roatation;
};
