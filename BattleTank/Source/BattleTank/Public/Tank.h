// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

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

	// Delegate aiming to this tanks aiming component.
	void aimAt(FVector worldLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	// Sets the turret reference for the aiming component
	void setTurretReference(UTankTurret* turretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	// Sets the barrel reference for the aiming component
	void setBarrelReference(UTankBarrel* barrelToSet);

protected:
	UTankAimingComponent* tankAimingComponent = nullptr;

private:	
	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 4000;
	
};
