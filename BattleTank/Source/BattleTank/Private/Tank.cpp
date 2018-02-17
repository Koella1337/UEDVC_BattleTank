// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	///add components to tank
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();

	lastFireTime = -reloadTimeInSeconds;		//make tanks able to fire immediately after spawning

	if (!tankAimingComponent) {
		UE_LOG(LogTemp, Error, TEXT("Tank [%s] is missing an Aiming Component!"), *GetName());
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::aimAt(FVector worldLocation) {
	tankAimingComponent->aimAt(worldLocation, launchSpeed);
}

void ATank::setTurretReference(UTankTurret* turretToSet) {
	tankAimingComponent->setTurret(turretToSet);
}

void ATank::setBarrelReference(UTankBarrel* barrelToSet) {
	tankAimingComponent->setBarrel(barrelToSet);
	barrel = barrelToSet;
}

void ATank::fire() {
	bool isReloaded = (GetWorld()->GetTimeSeconds() - lastFireTime) > reloadTimeInSeconds;

	if (barrel && isReloaded) {
		///spawn projectile at barrel's socket lockation
		auto spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			projectile,
			barrel->GetSocketLocation(FName("LaunchPoint")),
			barrel->GetSocketRotation(FName("LaunchPoint"))
			);

		if (spawnedProjectile)
			spawnedProjectile->launchProjectile(launchSpeed);
		else
			UE_LOG(LogTemp, Error, TEXT("Projectile could not be spawned! Is it set in the Tank Blueprint?"));

		lastFireTime = GetWorld()->GetTimeSeconds();
	}
}
