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
        Timer = Timer + 10.f;
        --TargetTowers;
    }
    else if (ABaseMinion* DestroyedMinion = Cast<ABaseMinion>(DeadActor))
    {
        DestroyedMinion->HandleDestruction();
        Timer = Timer + 10.f;
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
