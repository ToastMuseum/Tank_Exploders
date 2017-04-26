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
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *(OutHitLocation.ToString()));
		
		//TODO:  tell controlled tank to aim at this point
	}
}

//jdeo - Get world location of linetrace through crosshair, true if hits the landscape -jdeo
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	

	//"De-project" the screen position of the crosshair to a world direction
	// Linetrace along that look direction and see what we hit (up to max range)
	return true;
	
}