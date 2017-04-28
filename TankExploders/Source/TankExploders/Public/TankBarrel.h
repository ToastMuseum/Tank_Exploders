// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS()
class TANKEXPLODERS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:


public:
	void Elevate(float DegreesPerSecond);
	



};
