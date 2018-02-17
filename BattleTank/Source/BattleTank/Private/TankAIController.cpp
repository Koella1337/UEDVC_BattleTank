// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	controlledTank = Cast<ATank>(GetPawn());
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a Tank."));
	}

	playerTank = (ATank*) GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController didn't find a Player-Tank."));
	}
}

void ATankAIController::Tick(float deltaSeconds) {
	Super::Tick(deltaSeconds);

	if (controlledTank && playerTank) {
		///move towards the player
		MoveToActor(playerTank, acceptanceRadius);

		///aim towards the player
		controlledTank->aimAt(playerTank->GetActorLocation());

		///TODO: shoot if ready
		controlledTank->fire();
	}
}

ATank* ATankAIController::getControlledTank() const {
	return controlledTank;
}