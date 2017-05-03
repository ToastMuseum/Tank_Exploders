// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKEXPLODERS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Barrel Setup")
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = "Barrel Setup")
	float MinElevationDegrees = 0;

	UPROPERTY(EditAnywhere, Category = "Barrel Setup")
	float MaxDegreesPerSecond = 20;

public:
	void Elevate(float RelativeSpeed); //Max Speed (-1:MaxDownMovement +1:MaxUpMovement)	



};
