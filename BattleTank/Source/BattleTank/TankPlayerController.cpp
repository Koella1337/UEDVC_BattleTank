// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::getControlledTank() const {
	return Cast<ATank>(GetPawn());
}


