// Copyright BigD Games

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
	
	void AimAt(FVector OutHitLocation);


	UFUNCTION(BlueprintCallable, Category = "TankControls")
	void Fire();


private:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000; // jdeo - 6000 cm/s 
								
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;	//(Lec 145) Alternative to UClass*: TSubclassOf

	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3;

	UTankBarrel* Barrel = nullptr; // TODO: Remove

	double LastFireTime = 0;
};
