// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"		//TODO: remove when logging removed

void UTankTrack::setThrottle(float throttle) {
	//TODO: set actual throttle value so player cant speed tank up

	auto time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: %s's throttle: %f"), time, *GetName(), throttle);
}


