// Fill out your copyright notice in the Description page of Project Settings.


#include "TankExploders.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed) {


	if (!Barrel) {
		UE_LOG(LogTemp, Warning, TEXT("No Barrel Set"));
	}
	else {

		FVector OutLaunchVelocity;
		
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //Create a socket in BP editor on the barrel and grab it - jdeo
		
		// Calculate the OutLaunchVelocity
		bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			OutHitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			// default values need to be added if you want to skip to use a certain parameter,
			//they cannot be ommitted- jdeo
			FCollisionResponseParams::DefaultResponseParam,
			TArray<AActor*>(), // default -jdeo
			false
		);

		if(bHasAimSolution) {
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();

			MoveBarrelTowards(AimDirection);
		}
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	
	Barrel->Elevate(5); //TODO: remove magic number

}

