// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKEXPLODERS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UStaticMeshComponent* Barrel = nullptr;
	void MoveBarrelTowards (FVector AimDirection);

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//jdeo- public setter method
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	// TODO: Add SetTurretReference -jdeo

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

	
	
};
