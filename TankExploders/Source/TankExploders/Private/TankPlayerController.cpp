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

	//UE_LOG(LogTemp, Warning, TEXT("aiming crosshairs"));

	if (!GetControlledTank()) { return; }


	FVector OutHitLocation; //OutParameter -jdeo
	if (GetSightRayHitLocation(OutHitLocation)) { //Has "side-effect", is going to line trace -jdeo
		
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *(OutHitLocation.ToString()));

		GetControlledTank()->AimAt(OutHitLocation);
	}
}

//jdeo - Get world location of linetrace through crosshair, true if hits the landscape -jdeo
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	//mouse location on screen
	/* Testing MouseCoordinates on screen instead of crosshair reticle

	float X, Y;
	auto Mouse = GetMousePosition(X, Y);
	FVector2D MouseCoord = FVector2D (X, Y);
	if (!Mouse) {
		UE_LOG(LogTemp, Warning, TEXT("No Mouse Coords"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Mouse Coordinates: %s"), *(MouseCoord.ToString()));
	}
	*/


	//"De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)){
		// Linetrace along that look direction and see what we hit (up to max range)
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *(LookDirection.ToString()));
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	
	return true;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector CameraWorldLocation; // Discarded in output of this method-jdeo

	return DeprojectScreenPositionToWorld(ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		// Set hit location
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
	
}
