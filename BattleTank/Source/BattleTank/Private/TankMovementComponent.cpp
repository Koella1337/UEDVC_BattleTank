// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::initialise(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	this->leftTrack = leftTrack;
	this->rightTrack = rightTrack;
}

void UTankMovementComponent::intendMoveForward(float axisValue) {
	if (!leftTrack || !rightTrack) return;

	leftTrack->setThrottle(axisValue);
	rightTrack->setThrottle(axisValue);
	//TODO: prevent double speed via double control use
}

void UTankMovementComponent::intendTurnRight(float axisValue) {
	if (!leftTrack || !rightTrack) return;

	leftTrack->setThrottle(axisValue);
	rightTrack->setThrottle(-axisValue);
	//TODO: prevent double speed via double control use
}
