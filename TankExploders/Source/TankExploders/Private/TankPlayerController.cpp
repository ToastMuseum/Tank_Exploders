// Fill out your copyright notice in the Description page of Project Settings.


#include "TankExploders.h"
#include "TankPlayerController.h"



// BeginPlay -Jdeo
void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s: "), *(ControlledTank->GetName()));
	}
}


// Tick -Jdeo
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {

	UE_LOG(LogTemp, Warning, TEXT("aiming crosshairs"));
	
	if (!GetControlledTank()) { return;	}
	

	FVector OutHitLocation; //OutParameter -jdeo
	if (GetSightRayHitLocation(OutHitLocation)) { //Has "side-effect", is going to line trace -jdeo
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(OutHitLocation.ToString()));

		//TODO:  tell controlled tank to aim at this point
	}
}

//jdeo - Get world location of linetrace through crosshair, true if hits the landscape -jdeo
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
	
}