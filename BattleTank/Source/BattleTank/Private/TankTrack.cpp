// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"		//TODO: remove when logging removed

void UTankTrack::setThrottle(float throttle) {
	//TODO: clamp actual throttle value so player cant speed tank up
	
	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s's throttle: %f"), time, *GetName(), throttle);

	auto forceApplied = GetForwardVector() * throttle * trackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankBody->AddForceAtLocation(forceApplied, forceLocation);
}


