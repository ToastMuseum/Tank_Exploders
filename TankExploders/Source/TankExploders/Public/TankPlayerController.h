// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must Be Last Include -jdeo

class ATank;

/**
 * 
 */
UCLASS()
class TANKEXPLODERS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	
	 virtual void BeginPlay() override;

	 virtual void Tick(float DeltaSeconds) override;

protected:
	 UFUNCTION(BlueprintCallable, Category="Setup")
	 ATank* GetControlledTank() const;

private:
	//jdeo- start tank moving barrel so a shot would hit where
	// the crosshair intersects the world
	 void AimTowardsCrosshair();

	 //Return OUT parameter, true if hit landscape - jdeo
	 bool GetSightRayHitLocation(FVector& OutHitLocation) const;


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
