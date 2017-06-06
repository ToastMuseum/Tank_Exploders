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

protected:
	// Acceptance radius is moved into the protected class so the children can read it
	//How close enemy tank can get to player
	UPROPERTY(EditAnywhere, Category="Setup") //consider using EditDefaultsOnly
	float AcceptanceRadius = 8000; // [cm]

private:
	

public:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

		
};
