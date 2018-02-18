// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankAimingComponent;
class UTankBarrel;
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

	///Tank interface
	UTankAimingComponent* getAimingComponent() const;

	//Delegates aiming to the Aiming-Component
	void aimAt(FVector worldLocation) const;

	//TODO: move entire "Firing" category to AimingComponent
	UFUNCTION(BlueprintCallable, Category = "Firing")
	// Launches a projectile
	void fire();

private:
	///properties
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectile;

	//TODO: move entire "Firing" category to AimingComponent
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed = 4000;

	//TODO: move entire "Firing" category to AimingComponent
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTimeInSeconds = 3;

	///variables
	//time since last projectile was launched. initialized to -reloadTime at BeginPlay
	float lastFireTime;		

	// Local barrel reference for launching projectiles
	UTankBarrel* barrel = nullptr;

	UTankAimingComponent* aimingComp = nullptr;
};
