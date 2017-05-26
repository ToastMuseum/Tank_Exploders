// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Enum for aiming state
UENUM()
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked
};


//Forward Decalaration -jdeo
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds Barrel's properties and elevate method -jdeo
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKEXPLODERS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	bool CheckReferences();

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000; // jdeo - 6000 cm/s 

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;	//(Lec 145) Alternative to UClass*: TSubclassOf

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3;

	double LastFireTime = 0;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

public:	
	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = "TankControls")
	void Fire();
	
	
};
