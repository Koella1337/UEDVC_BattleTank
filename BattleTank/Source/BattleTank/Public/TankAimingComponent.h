// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"


#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	LockedOn,
	OutOfAmmo
};

///Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;



//Provides the interface from the Tank to it's Barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	// Executed every frame
	virtual void TickComponent(float, ELevelTick, FActorComponentTickFunction*) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void initialise(UTankTurret* turret, UTankBarrel* barrel);

	UFUNCTION(BlueprintCallable, Category = "Input")
	// Aims the Tank's turret&barrel towards a specific world-location.
	void aimAt(FVector worldLocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
	// Launches a projectile
	void fire();

	UFUNCTION(BlueprintCallable, Category = "State")
	int32 getAmmo() const;

	EFiringStatus getFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingState = EFiringStatus::Aiming;

private:
	///Variables
	UTankBarrel* barrel = nullptr;
	UTankTurret* turret = nullptr;

	float lastFireTime;				//time since last projectile was launched. initialized to -reloadTime at BeginPlay
	bool isBarrelMoving = false;	//set by aimAt-function, used for determineFireStatus()

	///Properties
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float launchSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float reloadTimeInSeconds = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 ammo = 20;
	
	///Private functions
	void moveBarrelTowards(FVector aimDirection);
	EFiringStatus determineFiringStatus() const;
};
