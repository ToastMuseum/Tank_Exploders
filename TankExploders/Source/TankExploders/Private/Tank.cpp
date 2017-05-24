// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s MEEP: Tank C++ Construct"), *TankName);
	
}


void ATank::BeginPlay() {

	Super::BeginPlay(); //Needed to run BP BeginPlay

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s MEEP: Tank C++ BeginPlay"), *TankName);
}


void ATank::AimAt(FVector OutHitLocation) {

	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed); 
}

void ATank::Fire() {

	if (!ensure(Barrel)) { return; }
	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds ;
	
	//if uncomfortable about using FPlatformTime::Seconds() use GetWorld()->GetTimeSeconds()
	auto Time = GetWorld()->GetTimeSeconds();
	auto Tank = this;
	if(ensure(Tank)){
		auto TankName = Tank->GetName();
		UE_LOG(LogTemp, Warning, TEXT(" Time: %f: %s: Shell fired"), Time, *TankName);
	}
	
	if (isReloaded) {
			
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

