// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * jdeo - This comment will appear when hovering over the Tank_BP track component.
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class TANKEXPLODERS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets a throttle between -1 and +1 -jdeo
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	
	//large enough to store our value so use float -jdeo
	////Max Force per track in Newtons [(kg*m)/s^2]
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; //Assume 40tonne tank, 1g acceleration
};
