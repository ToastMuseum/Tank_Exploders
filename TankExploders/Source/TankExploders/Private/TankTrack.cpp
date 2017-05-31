// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankTrack.h"



UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate the slippage speed (sideways component of speed)
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	
	// Work out required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	
	// Calculate and apply sideways force (F=ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //divide by two because two tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: Clamp actual throttle value so player cannot over-drive.
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //applied at track local origin on tank model

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	// TODO: Provide throttle for keyboard keys
}