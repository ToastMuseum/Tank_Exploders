// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed) {

	// Move the barrel the correct amount each frame -jdeo
	// Given a max elevation speed and the frame time
	
	//Clamp relative speed between -1 and +1 -jdeo
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

}