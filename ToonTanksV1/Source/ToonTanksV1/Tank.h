// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Tank.generated.h"
/**
 * 
 */
UCLASS()
class TOONTANKSV1_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestrucion();

	bool bPowerUpFireActive;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Fire();

private:

	UPROPERTY(EditAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USceneComponent* ProjectileSpawnPointA;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USceneComponent* ProjectileSpawnPointB;

	//Movement Variables	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 250.f;

	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.f;

	//Movement Functions
	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;

};
