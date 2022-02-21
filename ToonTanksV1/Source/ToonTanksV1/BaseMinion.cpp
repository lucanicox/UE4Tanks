// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMinion.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Tank.h"
#include "AIController.h"





// Sets default values
ABaseMinion::ABaseMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

}

void ABaseMinion::HandleDestruction() 
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	Destroy();
}

float ABaseMinion::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	
	if (DamageToApply <= 0.f) return DamageToApply;

	if (Health <= 0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(this);
	}

	return DamageToApply;
}

// Called when the game starts or when spawned
void ABaseMinion::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABaseMinion::AttackCondition, FireRate, true);

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

/* void ABaseMinion::Attack() 
{
	if (Attacking)
	{
		USkeletalMeshComponent* SkeletalMesh = GetMesh();
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		GetMesh()->SetAnimation(Attacking);
		GetMesh()->PlayAnimation(Attacking, false);

		if (Attacking->GetAnimNotifies())
		{
			
		}
		const USkeletalMeshSocket* WeaponSocket1 = GetMesh()->GetSocketByName(FName("Muzzle_Front_XForward"));
		const USkeletalMeshSocket* WeaponSocket2 = GetMesh()->GetSocketByName(FName("Muzzle_02"));
		FVector Start = WeaponSocket1->GetSocketLocation(SkeletalMesh);
		FVector End = WeaponSocket2->GetSocketLocation(SkeletalMesh);
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldDynamic, CollisionParams);

		AActor* HitActor = HitResult.GetActor();

		bAttacking = true;

		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
 	
} */

void ABaseMinion::AttackCondition() 
{
	if (Tank->IsHidden())
    {
 		bAttacking = false;
    }
    else if (InFireRange())
    {
		//Fire();
    }
}

bool ABaseMinion::InFireRange() 
{
	if (Tank)
    {    
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
            if (Distance <= FireRange)
            {
                return true;
            }
    }
    return false;
}

void ABaseMinion::Fire() 
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
	
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
}
/* void ABaseMinion::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	auto MyOwner = GetOwner();                //store owner* on local var
	if (MyOwner == nullptr)                   //Check nullptr
	{
		return;                                  
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();    //store damageinstigator on local var
	auto DamageTypeClass = UDamageType::StaticClass();
	
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)  //prevent damage to itself
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, NormalImpulse, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, MyOwnerInstigator, this);
		}
	}
} */

// Called every frame
void ABaseMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

