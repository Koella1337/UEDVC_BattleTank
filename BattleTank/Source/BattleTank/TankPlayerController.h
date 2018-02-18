// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"



#include "TankPlayerController.generated.h"		//must be last include


class ATank;	//forward declaration
class UTankAimingComponent;



UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	///Functions
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable, Category = "Tank")
	ATank* getControlledTank() const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void foundAimingComponent(UTankAimingComponent* aimCompRef);

private:
	///Functions
	void aimTowardsCrosshair();

	//raycast forward from the lookDirection to find a hit in sight
	bool getSightRayHitLocation(FVector& outHitLocation) const;

	//get the world-direction the player is looking at (with the crosshair)
	bool getLookDirection(FVector& outLookDirection) const;
	
	///Properties
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairXLocation = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairYLocation = 0.33f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float lineTraceRange = 1000000.0f; ///10km

	///Variables
	ATank* controlledTank = nullptr;
};
