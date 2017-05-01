// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{

	// jdeo-Default Sub-Object: No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// jdeo- delegate function to Set barrelreference with aiming component
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector OutHitLocation) {

	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed); 
}



