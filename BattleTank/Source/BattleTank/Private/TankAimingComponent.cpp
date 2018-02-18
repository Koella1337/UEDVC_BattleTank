// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
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
	if (!barrel || !turret) {
		UE_LOG(LogTemp, Error, TEXT("Missing Barrel or Turret on %s's AimingComponent!"), *GetOwner()->GetName());
		return;
	}

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

	///try to calculate an arc for launching the projectile from the barrel's end to worldLocation
	if (bFoundAimingSolution) {
		///found an arc -> launch the missile
		launchDirection = launchDirection.GetSafeNormal();	//convert provided velocity vector into unit vector
		moveBarrelTowards(launchDirection);
	}
	///if no solution found: do nothing
}

void UTankAimingComponent::initialise(UTankTurret* turret, UTankBarrel* barrel) {
	this->turret = turret;
	this->barrel = barrel;
}

//Expects barrel and turret to be valid since this is a private function.
void UTankAimingComponent::moveBarrelTowards(FVector aimDirection) {
	FRotator barrelRotator = barrel->GetComponentRotation();
	FRotator directionAsRotator = aimDirection.Rotation();
	FRotator deltaRotator = directionAsRotator - barrelRotator;

	turret->Rotate(deltaRotator.Yaw);
	barrel->Elevate(deltaRotator.Pitch);
}