// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	LockedOn
};

///Forward Declarations
class UTankBarrel;
class UTankTurret;





//Provides the interface from the Tank to it's Barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Input")
	// Aims the Tank's turret&barrel towards a specific world-location.
	void aimAt(FVector worldLocation, float launchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialise(UTankTurret* turretToSet, UTankBarrel* barrel);

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingStatus = EFiringStatus::Aiming;

private:
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;
	
	void moveBarrelTowards(FVector aimDirection);
};
