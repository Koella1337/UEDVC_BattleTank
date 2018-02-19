// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	//Register to receive "On Component Hit" events and declare the delegate
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

//Delegate for the Track's Blueprint-Event "On Component Hit", called every frame the Track is on the ground
void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hitResult) {
	driveTrack();
	correctSlipping();
	currentThrottle = 0;	//consume throttle after it was used
}

void UTankTrack::setThrottle(float throttle, bool isRotation) {
	if (isRotation) throttle *= rotationPriorityFactor;

	currentThrottle += throttle;
}

//Clamps the throttle between min and max and then uses it to apply force to the tank
void UTankTrack::driveTrack() {
	currentThrottle = FMath::Clamp<float>(currentThrottle, minThrottle, maxThrottle);

	FVector forceApplied = GetForwardVector() * currentThrottle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankBody->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::correctSlipping() {
	/// Work out required acceleration to correct slipping this frame: Acceleration = Speed / Time
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	float deltaTime = GetWorld()->GetDeltaSeconds();
	FVector correctionAcceleration = (-slippageSpeed / deltaTime) * GetRightVector();

	/// Calculate and apply sideways force to correct slipping: Force = Mass * Acceleration
	auto tankBody = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankBody->GetMass() * correctionAcceleration) / 2;	///Two tracks
	tankBody->AddForce(correctionForce);
}

