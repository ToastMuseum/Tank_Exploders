// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * responsible for driving the tank tracks -jdeo
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKEXPLODERS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category = Setup) //Allows method to be called in blueprint 
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* LeftTracktoSet, UTankTrack* RightTrackToSet);


};
