// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT(" %s intend move forward %f"), *Name, Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO: Prevent double speed due to double control use
}