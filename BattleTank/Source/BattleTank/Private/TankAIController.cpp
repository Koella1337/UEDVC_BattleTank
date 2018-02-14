// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto playerTank = getPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController didn't find a Player-Tank."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player that possesses Tank: %s"), *playerTank->GetName());
	}
}

ATank* ATankAIController::getPlayerTank() const {
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return playerPawn ? (ATank*) playerPawn : nullptr;
}
