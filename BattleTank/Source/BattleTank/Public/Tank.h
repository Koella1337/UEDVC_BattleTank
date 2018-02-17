// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankMovementComponent;
class UTankBarrel; class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///Tank Interface

	// Delegate aiming to this tanks aiming component.
	void aimAt(FVector worldLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	// Sets the turret reference for the aiming component
	void setTurretReference(UTankTurret* turretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	// Sets barrel reference locally and for the aiming component
	void setBarrelReference(UTankBarrel* barrelToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	// Launches a projectile
	void fire();

protected:
	UTankAimingComponent* tankAimingComponent = nullptr;

private:
	///properties
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> projectile;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeInSeconds = 3;

	///variables
	//time since last projectile was launched. initialized to -reloadTime at BeginPlay
	float lastFireTime;		

	// Local barrel reference for launching projectiles
	UTankBarrel* barrel = nullptr;
};
