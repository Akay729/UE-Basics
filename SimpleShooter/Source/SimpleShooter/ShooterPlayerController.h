// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="User Widget")
	TSubclassOf<class UUserWidget> LoseScreenClass;
	
	UPROPERTY(EditAnywhere, Category="User Widget")
	TSubclassOf<class UUserWidget> WinScreenClass;
	
	UPROPERTY(EditAnywhere, Category="User Widget")
	TSubclassOf<class UUserWidget> HUDScreenClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 3.0f;

	FTimerHandle RestartTimer;

	UFUNCTION()
	UUserWidget* CreateWidgetFromClass(TSubclassOf<class UUserWidget> WidgetClass);
};
