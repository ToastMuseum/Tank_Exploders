// Copyright BigD Games

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //jdeo- must put new #includes about the generated.h 

//Forward declarations -jdeo
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class TANKEXPLODERS_API ATank : public APawn
{
	GENERATED_BODY() 


public:
	// Sets default values for this pawn's properties
	ATank();
	

	//TODO: Remove once firing is moved to aiming component
	UFUNCTION(BlueprintCallable, Category = "TankControls")
	void Fire();


private:
	virtual void BeginPlay() override;
								
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;	//(Lec 145) Alternative to UClass*: TSubclassOf

	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3;

	UTankBarrel* Barrel = nullptr; // TODO: Remove

	double LastFireTime = 0;

	//TODO: Remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 8000; // jdeo - 6000 cm/s 
};
