// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //jdeo- must put new #includes about the generated.h 



class UTankBarrel; //Forward declaration -jdeo

UCLASS()
class TANKEXPLODERS_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// jdeo- cant be private because this is being accessed through a Ucomponent 
	//			and it should not be public because it should not be accessed
	//			outside of the tank

	UTankAimingComponent* TankAimingComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)	//jdeo- creates a method we can call from blueprint editor
	void SetBarrelReference(UTankBarrel* BarrelToSet);

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; // jdeo - 1000 m/s 
								//TODO: Find Sensible default value
	
};
