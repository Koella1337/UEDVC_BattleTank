// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::initialise(UTankTrack* leftTrack, UTankTrack* rightTrack) {
	this->leftTrack = leftTrack;
	this->rightTrack = rightTrack;
}

void UTankMovementComponent::intendMoveForward(float axisValue) {
	if (!ensure(leftTrack && rightTrack)) return;

	leftTrack->setThrottle(axisValue);
	rightTrack->setThrottle(axisValue);
	//TODO: prevent double speed via double control use
}

void UTankMovementComponent::intendTurnRight(float axisValue) {
	if (!ensure(leftTrack && rightTrack)) return;

	leftTrack->setThrottle(axisValue);
	rightTrack->setThrottle(-axisValue);
	//TODO: prevent double speed via double control use
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	///replacing functionality --> no Super!

	FVector aiMoveIntention = MoveVelocity.GetSafeNormal();
	float aiForwardAxis = FVector::DotProduct(GetOwner()->GetActorForwardVector(), aiMoveIntention);
	float aiRightAxis = FVector::DotProduct(GetOwner()->GetActorRightVector(), aiMoveIntention);
	//Alternative: float aiRightAxisCross = FVector::CrossProduct(GetOwner()->GetActorForwardVector(), aiMoveIntention).Z;

	intendMoveForward(aiForwardAxis);
	intendTurnRight(aiRightAxis);
}
