// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();

	// Getting the Root component for the UStaticMeshComponent so we can SimulatePhysics on beginPlay() 
	// This eliminates the tank in terrain bug -jdeo
	auto TankRoot = Cast<UStaticMeshComponent>(GetRootComponent());
	//TankRoot->SetSimulatePhysics(false);
	TankRoot->SetSimulatePhysics(true);

	CurrentHealth = MaxHealth;

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/ (float)MaxHealth;
}



