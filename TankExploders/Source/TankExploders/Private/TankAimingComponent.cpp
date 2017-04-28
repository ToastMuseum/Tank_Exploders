// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...

	

}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed) {


	if (!Barrel) {
		UE_LOG(LogTemp, Warning, TEXT("No Barrel Set"));
	}
	else {

		FVector OutLaunchVelocity;
		
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); //Create a socket in BP editor on the barrel and grab it - jdeo
		
		// Calculate the OutLaunchVelocity
		if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			OutHitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			FCollisionResponseParams::DefaultResponseParam, // default values need to be added, they cannot be skipped- jdeo
			TArray<AActor*>(), // default -jdeo
			false
		)) {

			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			auto TankName = GetOwner()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("%s is Aiming at: %s"), *(TankName), *(AimDirection.ToString()));
		}
	}
}

