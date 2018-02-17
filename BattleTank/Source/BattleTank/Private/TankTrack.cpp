// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"

void UTankTrack::setThrottle(float throttle) {
	float clampedThrottle = FMath::Clamp<float>(throttle, -0.7f, 1.0f);
	
	FVector forceApplied = GetForwardVector() * clampedThrottle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankBody->AddForceAtLocation(forceApplied, forceLocation);
}


