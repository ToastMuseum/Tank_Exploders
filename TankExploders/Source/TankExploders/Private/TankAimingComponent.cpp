// Fill out your copyright notice in the Description page of Project Settings.


#include "TankExploders.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}

void UTankAimingComponent::BeginPlay() {

	// So first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
	if (RoundsLeft <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else 
	{
		FiringState = EFiringState::Locked;
	}

	
	//TODO: Handle Aiming and Locked states
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

EFiringState UTankAimingComponent::GetFiringState() const 
{
	return FiringState;
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}


bool UTankAimingComponent::CheckReferences() {
	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Warning, TEXT("Barrel Not Set"));
		return true;
	}
	if (!ensure(Turret)) {
		UE_LOG(LogTemp, Warning, TEXT("Turret Not Set"));
		return true;
	}
	return false;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation) {

	bool bNoReferences = CheckReferences();
	if (bNoReferences) {
		
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
			0
			,ESuggestProjVelocityTraceOption::DoNotTrace, //TODO: Report Bug: Parameter must be present to prevent bug

			// default values need to be added if you want to skip to use a certain parameter,
			//they cannot be ommitted- jdeo
			FCollisionResponseParams::DefaultResponseParam,
			TArray<AActor*>(), // default -jdeo
			false
		);

		if(bHasAimSolution) {
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveBarrelTowards();

			/*TODO: Remove This Later. This is for reference on GetOwner and GetWorld
			auto Time = GetWorld()->GetTimeSeconds(); 
			auto TankName = GetOwner()->GetName();
			UE_LOG(LogTemp, Warning, TEXT(" Time: %f: %s Aim Solution Found"), Time, *TankName);
			*/
		}
		//If no aim solution found do nothing
	}

}


void UTankAimingComponent::MoveBarrelTowards() {

	if (!ensure(Barrel && Turret)) { return; }

	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	
	
	Barrel->Elevate(DeltaRotator.Pitch);

	//GetNormalized fixes Awkward turret rotation bug
	Turret->RotateTurret(DeltaRotator.GetNormalized().Yaw);

	//Another way to rotate the turret properly
	/*
	if (FMath::Abs(DeltaRotator.Yaw) < 180){
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else {
		Turret->RotateTurret(-DeltaRotator.Yaw);
	*/
	
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto TankForwardVector = Barrel->GetForwardVector();
	
	return !TankForwardVector.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire() {


	//if uncomfortable about using FPlatformTime::Seconds() use GetWorld()->GetTimeSeconds()
	auto Time = GetWorld()->GetTimeSeconds();
	auto Tank = this;
	if (ensure(Tank)) {
		auto TankName = Tank->GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT(" Time: %f: %s: Shell fired"), Time, *TankName);
	}

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {

		//Spawn rojectile at socket location on barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		NewProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;

	}



}


