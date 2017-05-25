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


// Holds Barrel's properties and elevate method -jdeo
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKEXPLODERS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	// Sets default values for this component's properties
	UTankAimingComponent();


	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	bool CheckReferences();

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000; // jdeo - 6000 cm/s 


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

public:	
	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void AimAt(FVector OutHitLocation);


	
	
};
