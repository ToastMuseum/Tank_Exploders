// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		//TODO: Move Toward Player

		//Aim Towards player
		//FVector OutHitLocation;
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		//TODO: limit Fire rate
		ControlledTank->Fire();
	}
}

