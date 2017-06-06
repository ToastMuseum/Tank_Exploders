// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
//Depends on movement component via pathfinding system



void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	if (!ensure(PlayerTank) && ControlledTank) {return;}
	//TODO: Move Toward Player
	MoveToActor(PlayerTank,	AcceptanceRadius); //TODO: Check radius is in cm

	//Aim Towards player
	//FVector OutHitLocation;
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
	//TODO: limit Fire rate
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire(); //TODO: Fix Firing
	}
}

