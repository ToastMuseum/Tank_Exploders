// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankTurret.h"



void UTankTurret::RotateTurret(float RelativeSpeed) {

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	//auto ClampedRotation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator( 0, RawNewRotation,  0));
}
