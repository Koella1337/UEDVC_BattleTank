// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

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

	bool bFoundAimingSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT launchDirection,
		barrel->GetSocketLocation(FName("LaunchPoint")),
		worldLocation,
		launchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace		//Parameter must be present to prevent bug
	);

	auto time = GetWorld()->GetTimeSeconds();
	///try to calculate an arc for launching the projectile from the barrel's end to worldLocation
	if (bFoundAimingSolution) {
		///found an arc -> launch the missile
		launchDirection = launchDirection.GetSafeNormal();	//convert provided velocity vector into unit vector
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found."), time);
		moveBarrelTowards(launchDirection);
	} else
		UE_LOG(LogTemp, Warning, TEXT("%f: DID NOT find aim solution."), time);
	///if no solution found: do nothing
}

void UTankAimingComponent::setBarrel(UTankBarrel* barrelToSet) {
	barrel = barrelToSet;
}

void UTankAimingComponent::setTurret(UTankTurret* turretToSet) {
	turret = turretToSet;
}


void UTankAimingComponent::moveBarrelTowards(FVector aimDirection) {
	FRotator barrelRotator = barrel->GetComponentRotation();
	FRotator directionAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = directionAsRotator - barrelRotator;

	turret->Rotate(deltaRotator.Yaw);
	barrel->Elevate(deltaRotator.Pitch);
}