// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include"Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "BaseMinion.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"


void AToonTanksGameMode::ActorDied(AActor* DeadActor) 
{
    if (DeadActor == Tank)                                             // check if dead actor is player
    {
        Tank->HandleDestrucion();                                      // call function on player to destroy
        if (ToonTanksPlayerController)                                 // check if player function on getcontroller is valid                  
        {
            ToonTanksPlayerController->SetPlayerEnableState(false);
        }
        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        Seconds = Seconds + 5;
        Score = Score + 100;
        if (Seconds > 60)
        {
            Minutes = Minutes +1;
            Seconds = Seconds - 60;
        }
        --TargetTowers;
    }
    else if (ABaseMinion* DestroyedMinion = Cast<ABaseMinion>(DeadActor))
    {
        DestroyedMinion->HandleDestruction();
        Seconds = Seconds + 5;
        Score = Score + 150;
        if (Seconds > 60)
        {
            Minutes = Minutes +1;            
            Seconds = Seconds - 60;
        }
        --TargetMinions;
    }
}

void AToonTanksGameMode::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart(); 
}
    
void AToonTanksGameMode::HandleGameStart() 
{

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));      //set pawn var
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnableState(false);
        
        FTimerHandle PlayerEnableTimerHandle;               //create timerhandle                          
        FTimerDelegate DelayDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true); //create delegate
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, DelayDelegate, StartDelay, false);   //pass handle & delegate + params to SetTimer()

        FTimerHandle TimerHandleCountdown;
        GetWorldTimerManager().SetTimer(TimerHandleCountdown, this, &AToonTanksGameMode::Countdown, 1.f, true, 3.0);
    }
    
}

void AToonTanksGameMode::Countdown() 
{
    if (Seconds != 0 )
    {
        Seconds = Seconds - 1;
    }
    /* else if (Seconds >= 60)
        {
            Minutes = Minutes +1;
            Seconds = 0;
        } */
    else
    {
        if (Minutes == 0 && Seconds <= 0)
        {
            GameOver(false);
        }
        
        else
        {
            Minutes = Minutes -1;
            Seconds = 59;
        }
    }
}

int32 AToonTanksGameMode::GetTargetTowerCounter() 
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}

int32 AToonTanksGameMode::GetTargetMinionsCounter() 
{
    TArray<AActor*> Minions;
    UGameplayStatics::GetAllActorsOfClass(this, ABaseMinion::StaticClass(), Minions);
    return Minions.Num();
}
