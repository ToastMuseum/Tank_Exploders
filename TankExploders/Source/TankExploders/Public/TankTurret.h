// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( meta=(BlueprintSpawnableComponent))
class TANKEXPLODERS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	//TODO: Put in variables -jdeo
	UPROPERTY(EditAnywhere, Category = "Turret Setup")
	float MaxDegreesPerSecond = 20;
	//rotationCorrection so tank doesnt wig out going from 0 to 180 and then -180 to 0,
	


public:
	//TODO: Method for rotating turrets yaw component -jdeo
	void RotateTurret(float RelativeSpeed);
	
	
};
