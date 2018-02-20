// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	aimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	ensure(aimingComp);

	playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ensure(playerPawn);
}

void ATankAIController::Tick(float deltaSeconds) {
	Super::Tick(deltaSeconds);

	if (ensure(aimingComp && playerPawn)) {
		///move towards the player
		MoveToActor(playerPawn, acceptanceRadius);

		///aim towards the player
		aimingComp->aimAt(playerPawn->GetActorLocation());
		
		///shoot if ready
		if (aimingComp->getFiringState() == EFiringStatus::LockedOn) {
			aimingComp->fire();
		}
	}
}