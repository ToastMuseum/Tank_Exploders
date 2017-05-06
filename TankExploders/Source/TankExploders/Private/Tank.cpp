// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{

	// jdeo-Default Sub-Object: No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
}

// jdeo- delegate function to Set barrelreference with aiming component
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

// jdeo- delegate function to Set turretreference with aiming component
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector OutHitLocation) {

	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed); 
}

void ATank::Fire() {
	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds ;
	
	//if uncomfortable about using FPlatformTime::Seconds() use GetWorld()->GetTimeSeconds()
	auto Time = GetWorld()->GetTimeSeconds();
	auto Tank = this;
	if(Tank){
		auto TankName = Tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT(" Time: %f: %s: Shell fired"), Time, *TankName);
	}
	
	if (Barrel && isReloaded) {
			
		//Spawn rojectile at socket location on barrel
		auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		NewProjectile->LaunchProjectile(LaunchSpeed);
		

		LastFireTime = FPlatformTime::Seconds();
	
	}

	

}

