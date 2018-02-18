// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankMovementComponent.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();

	lastFireTime = -reloadTimeInSeconds;		//make tanks able to fire immediately after spawning

	///Set up locally-stored components
	barrel = FindComponentByClass<UTankBarrel>();
	aimingComp = FindComponentByClass<UTankAimingComponent>();

	if (!barrel)
		UE_LOG(LogTemp, Error, TEXT("Tank [%s] can't find its Barrel!"), *GetName());
	if (!aimingComp) 
		UE_LOG(LogTemp, Error, TEXT("Tank [%s] can't find its Aiming-Component!"), *GetName());
}

UTankAimingComponent* ATank::getAimingComponent() const {
	return aimingComp;
}

void ATank::aimAt(FVector worldLocation) const {
	if (aimingComp)
		aimingComp->aimAt(worldLocation, launchSpeed);
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
