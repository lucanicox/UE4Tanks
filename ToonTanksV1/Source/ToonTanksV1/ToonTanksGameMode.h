// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKSV1_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DeadActor);        // function to implement for dead actor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Minutes = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Seconds = 0;

	void AddScore();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score = 0;

private:

	class ATank* Tank;                        // declare class var pointer for player
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	void Countdown();

	int32 TargetTowers = 0;
	int32 GetTargetTowerCounter();

	int32 TargetMinions = 0;
	int32 GetTargetMinionsCounter();
	
};
