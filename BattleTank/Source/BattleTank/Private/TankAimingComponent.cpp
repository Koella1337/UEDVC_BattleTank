// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"

#define OUT 

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::aimAt(FVector worldLocation, float launchSpeed) {
	if (!barrel) return;

	//unitvector that tells us in which direction the projectile needs to be launched
	FVector launchDirection;

	///try to calculate an arc for launching the projectile from the barrel's end to worldLocation
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT launchDirection,
		barrel->GetSocketLocation(FName("LaunchPoint")),
		worldLocation,
		launchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
	) {
		///found an arc -> launch the missile
		launchDirection = launchDirection.GetSafeNormal();	//convert provided velocity vector into unit vector
		moveBarrelTowards(launchDirection);
	}
	///if no solution found: do nothing
}

void UTankAimingComponent::setBarrel(UTankBarrel* barrelToSet) {
	barrel = barrelToSet;
}


void UTankAimingComponent::moveBarrelTowards(FVector aimDirection) {
	FRotator barrelRotator = barrel->GetComponentRotation();
	FRotator directionAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = directionAsRotator - barrelRotator;

	barrel->Elevate(5.0f); //TODO: remove magic number
}