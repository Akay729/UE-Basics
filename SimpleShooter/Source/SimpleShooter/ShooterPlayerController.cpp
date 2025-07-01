// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    // UE_LOG(LogTemp, Display, TEXT("Shooter PC"));
    UUserWidget* HUD = CreateWidgetFromClass(HUDScreenClass);
    if (HUD)
    {
        HUD->RemoveFromViewport();
    }
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }  
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }
    

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
    
    UUserWidget* HUD = CreateWidgetFromClass(HUDScreenClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }  
}

UUserWidget* AShooterPlayerController::CreateWidgetFromClass(TSubclassOf<class UUserWidget> WidgetClass)
{
    if (!WidgetClass) return nullptr;
    UUserWidget* widget = CreateWidget(this, WidgetClass);
    return widget;
}
