// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* controlledTank = getControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a Tank."));
	}

	auto playerTank = getPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController didn't find a Player-Tank."));
	}
}

void ATankAIController::Tick(float deltaSeconds) {
	Super::Tick(deltaSeconds);

	if (getControlledTank() && getPlayerTank()) {
		///aim towards the player
		getControlledTank()->aimAt(getPlayerTank()->GetActorLocation());

		///TODO: move towards the player


		///TODO: shoot if ready

	}
}

ATank* ATankAIController::getControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::getPlayerTank() const {
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return playerPawn ? (ATank*) playerPawn : nullptr;
}