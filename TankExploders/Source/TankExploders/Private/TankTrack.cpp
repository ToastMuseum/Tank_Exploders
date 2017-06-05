// Fill out your copyright notice in the Description page of Project Settings.

#include "TankExploders.h"
#include "TankTrack.h"



UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	//generate onhit events in cpp -jdeo
	//Register delegate at begin play - jdeo
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	UE_LOG(LogTemp, Warning, TEXT("Current Throttle: %f"), CurrentThrottle);
	CurrentThrottle = 0;
}




void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slippage speed (sideways component of speed)
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work out required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways force (F=ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //divide by two because two tracks
	TankRoot->AddForce(CorrectionForce);
}




void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	// TODO: Clamp actual throttle value so player cannot over-drive.
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //applied at track local origin on tank model

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	// TODO: Provide throttle for keyboard keys
}
