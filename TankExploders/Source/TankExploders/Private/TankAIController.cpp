// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	auto AITank = GetControlledTank();

	if (!AITank) {
		UE_LOG(LogTemp, Warning, TEXT("No AI Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Possesed AI Tank: %s"), *(AITank->GetName()));

	}
}


ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}