// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float relativeSpeed) {
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, +1);
	float rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();

	float newRotation = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0, newRotation, 0));
}


