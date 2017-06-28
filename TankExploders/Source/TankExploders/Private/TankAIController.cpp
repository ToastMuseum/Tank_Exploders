// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h" // for SetPawn to be able to cast InPawn as a tank -jdeo
//Depends on movement component via pathfinding system



void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }
		UE_LOG(LogTemp, Warning, TEXT("In Pawn"));
		//subscribe our local method to the tanks death event - jdeo
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath() {

	//UE_LOG(LogTemp, Warning, TEXT("AI Tank Ded"));
	if (!GetPawn()) { return; } //TODO: Remove ensure if ok
	GetPawn()->DetachFromControllerPendingDestroy(); 
}


void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	if (!PlayerTank && ControlledTank) {return;}
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

