// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must Be Last Include -jdeo

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

	 ATank* GetControlledTank() const;

private:
	//jdeo- start tank moving barrel so a shot would hit where
	// the crosshair intersects the world
	 void AimTowardsCrosshair();

	 //Return OUT parameter, true if hit landscape - jdeo
	 bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	 UPROPERTY (EditAnywhere)
	 float CrosshairXLocation = 0.5;

	 UPROPERTY(EditAnywhere)
	 float CrosshairYLocation = 0.3333;

};
