// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class TANKEXPLODERS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	//How close enemy tank can get to player
	float AcceptanceRadius = 3000; // [cm]

public:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

		
};
