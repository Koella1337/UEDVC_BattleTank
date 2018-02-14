// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* controlledTank = getControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a Tank."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing Tank ID: %s"), *controlledTank->GetName());
	}	
}

ATank* ATankPlayerController::getControlledTank() const {
	return Cast<ATank>(GetPawn());
}
