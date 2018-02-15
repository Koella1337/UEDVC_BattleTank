// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);
	float elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();

	float rawNewElevation = RelativeRotation.Pitch + elevationChange;
	float clampedNewElevation = FMath::Clamp<float>(rawNewElevation, minElevationDegrees, maxElevationDegrees);

	SetRelativeRotation(FRotator(clampedNewElevation, 0, 0));
}


