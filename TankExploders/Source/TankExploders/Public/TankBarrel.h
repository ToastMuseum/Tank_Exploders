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
	float MaxDegrees = 30;

	UPROPERTY(EditAnywhere, Category = "Barrel Setup")
	float MinDegrees = 0;

	UPROPERTY(EditAnywhere, Category = "Barrel Setup")
	float MaxDegreesPerSecond = 5;

public:
	void Elevate(float DegreesPerSecond);
	



};
