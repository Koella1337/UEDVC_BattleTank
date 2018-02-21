// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "Public/Tank.h"

#define OUT 

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	aimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(aimingComp))
		foundAimingComponent(aimingComp);
}

void ATankPlayerController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);

	if (InPawn) {
		auto possessedTank = Cast<ATank>(InPawn);
		if (ensure(possessedTank)) {
			possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::onTankDeath);
		}
	}
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	if (GetPawn()) { //only execute when Controller is possessing a Pawn
		aimTowardsCrosshair();
	}
}

void ATankPlayerController::onTankDeath() {
	StartSpectatingOnly();
	UnPossess();
}

void ATankPlayerController::aimTowardsCrosshair() {
	if (!ensure(aimingComp)) return;

	FVector hitLocation = FVector::ZeroVector;
	if (getSightRayHitLocation(OUT hitLocation)) {		//side-effect: actually does the raytrace into hitLocation
		aimingComp->aimAt(hitLocation);
	}
}

bool ATankPlayerController::getSightRayHitLocation(FVector& outHitLocation) const {
	///get the direction we want to raycast in
	FVector lookDirection;
	if (getLookDirection(OUT lookDirection)) {
		///linetrace forward into the lookDirection
		FVector startLocation = PlayerCameraManager->GetCameraLocation();
		FVector endLocation = startLocation + lookDirection * lineTraceRange;
		FHitResult linetraceHitResult;

		if (GetWorld()->LineTraceSingleByChannel(
				OUT linetraceHitResult,
				startLocation,
				endLocation,
				ECC_Camera,
				FCollisionQueryParams(NAME_None, false, GetPawn())
			)
		) {
			///if linetrace hits anything: return the impact location and true
			outHitLocation = linetraceHitResult.Location;
			return true;
		}		
	}

	///else: return zero-vector and false
	return false;
}

bool ATankPlayerController::getLookDirection(FVector& outLookDirection) const {
	///find crosshair position on screen
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(OUT viewportSizeX, OUT viewportSizeY);
	FVector2D crosshairLocation = FVector2D(viewportSizeX * CrossHairXLocation, viewportSizeY * CrossHairYLocation);

	///deproject it into a worldDirection
	FVector cameraWorldLocation;	//ignored
	return DeprojectScreenPositionToWorld(crosshairLocation.X, crosshairLocation.Y, OUT cameraWorldLocation, OUT outLookDirection);
}
