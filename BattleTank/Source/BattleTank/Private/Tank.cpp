// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"

// Sets default values
ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();

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

void ATank::setBarrelReference(UTankBarrel* barrelToSet) {
	tankAimingComponent->setBarrel(barrelToSet);
}
