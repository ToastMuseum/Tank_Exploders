// Copyright BigD Games

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must Be Last Include -jdeo

class UTankAimingComponent;


/**
 * Responsible for helping the player aim.
 */
UCLASS()
class TANKEXPLODERS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	
	 virtual void BeginPlay() override;

	 virtual void Tick(float DeltaSeconds) override;

protected:


	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	//jdeo- start tank moving barrel so a shot would hit where
	// the crosshair intersects the world
	 void AimTowardsCrosshair();

	 //Return OUT parameter, true if hit landscape - jdeo
	 bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	 virtual void SetPawn(APawn* InPawn) override;

	 UFUNCTION()
	 void OnPossessedTankDeath();


	 UPROPERTY (EditDefaultsOnly)
	 float CrosshairXLocation = 0.5;

	 UPROPERTY(EditDefaultsOnly)
	 float CrosshairYLocation = 0.3333;

	 /*jdeo- const because Getting the look direction is not going to be changing
			any of the member variables of this class
	*/
	 bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	 bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	 UPROPERTY(EditDefaultsOnly)
	 float LineTraceRange = 1000000; //cm to km
};
