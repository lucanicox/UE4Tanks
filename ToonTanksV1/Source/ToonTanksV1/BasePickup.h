// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Tank.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "BasePickup.generated.h"



UCLASS()
class TOONTANKSV1_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 

	class ATank* Tank;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;

	float SphereRadius;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* ParticleIdle;

	/* UPROPERTY(EditAnywhere)
	class UNiagaraComponent* ParticlePicked; */

	UPROPERTY(EditAnywhere, Category = "Type")
	bool FirePickup;

	UPROPERTY(EditAnywhere, Category = "Type")
	bool HealthPickup;

	UPROPERTY(EditAnywhere, Category = "Type")
	bool TeleportPickup;

	UPROPERTY(EditAnywhere, Category = "Type")
	FVector TeleportLocation;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
