// Fill out your copyright notice in the Description page of Project Settings.


#include "TankExploders.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"


// BeginPlay -Jdeo
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s: "), *(ControlledTank->GetName()));


	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {return;}
	//Broadcasting this event 
	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//register BroadcastingInstance to subscribe our local method to the tanks death event - jdeo 
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}

}

void ATankPlayerController::OnPossessedTankDeath() {
	StartSpectatingOnly();
}

// Tick -Jdeo
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}




void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetPawn()) { return; } // if not possessing

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation; //OutParameter -jdeo
	bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
	if (bGotHitLocation) { //Has "side-effect", is going to line trace -jdeo
		
		AimingComponent->AimAt(OutHitLocation);
	}
}

//jdeo - Get world location of linetrace through crosshair, true if hits the landscape -jdeo
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	//TODO: Decide if we want to use mouse location on screen
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
		return GetLookVectorHitLocation(LookDirection, OutHitLocation); // Tank barrel does not reset to zero -jdeo
		//GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false; //TankBarrel doesn't reset to zero -jdeo
	//return true;
	
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
		ECollisionChannel::ECC_Camera
	)) {
		// Set hit location
		OutHitLocation = HitResult.Location;
		return true;
	}

	/* TODO: Remove this later. This is for reference on finding look direction
	auto TankName = GetControlledTank()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: No LookDirection Found"), *(TankName));
	*/


	OutHitLocation = FVector(0);
	return false;
	
}
