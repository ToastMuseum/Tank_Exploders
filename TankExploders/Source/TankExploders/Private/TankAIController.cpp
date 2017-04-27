// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankAIController.h"




void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	auto PlayerPawn = GetPlayerTank();

	if (!PlayerPawn) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Not Found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank: %s"), *(PlayerPawn->GetName()));

	}
}


// Get Controlled Tank -jdeo
ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}


// Get Player Tank -jdeo
ATank* ATankAIController::GetPlayerTank() const {

	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
}