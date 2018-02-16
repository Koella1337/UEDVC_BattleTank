// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"

#define OUT 

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	controlledTank = Cast<ATank>(GetPawn());
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a Tank."));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	aimTowardsCrosshair();
}

ATank* ATankPlayerController::getControlledTank() const {
	return controlledTank;
}

void ATankPlayerController::aimTowardsCrosshair() {
	if (!controlledTank) return;

	FVector hitLocation;
	if (getSightRayHitLocation(OUT hitLocation)) {		//side-effect: actually does the raytrace into hitLocation
		controlledTank->aimAt(hitLocation);
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
				ECC_Visibility,
				FCollisionQueryParams(NAME_None, false, controlledTank)
			)
		) {
			///if linetrace hits anything: return the impact location and true
			outHitLocation = linetraceHitResult.Location;
			return true;
		}		
	}

	///else: return zero-vector and false
	outHitLocation = FVector::ZeroVector;
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
