// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void SetPawn(APawn* InPawn) override;

private:
	UTankAimingComponent* aimingComp = nullptr;
	APawn* playerPawn = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// The radius in cm where the AI considers itself close enough to the player
	float acceptanceRadius = 6500;

	UFUNCTION()
	void onTankDeath();
};
