// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EEnemyState
{
	Idle UMETA(DisplayName = "Idle"),
	Range UMETA(DisplayName = "Range"),
	Charge UMETA(DisplayName = "Charge"),
	Melee UMETA(DisplayName = "Melee"),
	Patrol UMETA(DisplayName = "Patrol"),
	Chase UMETA(DisplayName = "Chase"),
	Block UMETA(DisplayName = "Block"),
	Damaged UMETA(DisplayName = "Damaged"),
	Dead UMETA(DisplayName = "Dead"),
	GameOver UMETA(DisplayName = "Game Over")
};