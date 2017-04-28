// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float DegreesPerSecond) {

	// Move the barrel the correct amount each frame
	// Given a max elevation speed and the frame time

	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT(" Barrel->Elevate() called: %s"), *TankName);
}