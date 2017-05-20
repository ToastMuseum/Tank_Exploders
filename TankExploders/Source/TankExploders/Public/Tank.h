// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //jdeo- must put new #includes about the generated.h 

//Forward declarations -jdeo
class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class TANKEXPLODERS_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// jdeo- cant be private because this is being accessed through a Ucomponent 
	//			and it should not be public because it should not be accessed
	//			outside of the tank

	// TankAimingComponent required so put "TankAimingComponent.h" in Tank.cpp -jdeo
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;  

	UPROPERTY(BlueprintReadOnly) // Makes readable from blueprint
	UTankMovementComponent* TankMovementComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)	//jdeo- creates a method we can call from blueprint editor
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = TankControls)
	void Fire();


private:
	//local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 8000; // jdeo - 6000 cm/s 
								
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;	//(Lec 145) Alternative to UClass*: TSubclassOf

	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeSeconds = 3;

	double LastFireTime = 0;
};
