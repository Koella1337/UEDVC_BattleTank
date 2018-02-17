// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"		//TODO: remove when logging removed

void UTankTrack::setThrottle(float throttle) {
	float clampedThrottle = FMath::Clamp<float>(throttle, -0.7f, 1.0f);
	
	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s's throttle: %f"), time, *GetName(), throttle);
	
	FVector forceApplied = GetForwardVector() * clampedThrottle * trackMaxDrivingForce;
	FVector forceLocation = GetComponentLocation();
	auto tankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankBody->AddForceAtLocation(forceApplied, forceLocation);
}


