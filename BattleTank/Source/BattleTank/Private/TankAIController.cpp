// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "Public/Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	aimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	ensure(aimingComp);

	player = GetWorld()->GetFirstPlayerController();
	ensure(player);
}

void ATankAIController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto possessedTank = Cast<ATank>(InPawn);
		if (ensure(possessedTank)) {
			possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::onTankDeath);
		}
	}
}

void ATankAIController::Tick(float deltaSeconds) {
	Super::Tick(deltaSeconds);

	if (ensure(aimingComp && player)) {
		auto playerPawn = player->GetPawn();
		if (!playerPawn) return;			//do nothing if player doesn't possess a Pawn

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

void ATankAIController::onTankDeath() {
	if (!ensure(GetPawn())) return;
	GetPawn()->DetachFromControllerPendingDestroy();
}
