// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONCOMBAT_API IEnemy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enemy")
	void OnSelect(); // Called when the enemy is selected for combat
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enemy")
	void OnDeselect(); // Called when the enemy is selected for combat
};
