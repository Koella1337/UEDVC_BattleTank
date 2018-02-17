// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* getControlledTank() const;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

private:
	ATank* controlledTank = nullptr;
	ATank* playerTank = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// The radius in cm where the AI considers itself close enough to the player
	float acceptanceRadius = 3000;
};
