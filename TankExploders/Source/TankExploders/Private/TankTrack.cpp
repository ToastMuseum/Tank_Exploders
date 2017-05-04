// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT(" %s throttle %f"), *Name, Throttle);

	// TODO: Clamp actual throttle value so player cannot over-drive.
	// TODO: Provide throttle for keyboard keys
}