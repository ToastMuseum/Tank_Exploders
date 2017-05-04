// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: Clamp actual throttle value so player cannot over-drive.
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //applied at track local origin on tank model

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	// TODO: Provide throttle for keyboard keys
}