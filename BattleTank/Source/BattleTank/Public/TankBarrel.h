// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"



#include "TankBarrel.generated.h"
 
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = (Collision, Physics, Rendering, Cooking, Mobile) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward movement, +1 is max upward movement
	void Elevate(float relativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond = 20;			//sensible default
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees = -3;			//sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees = 35;			//sensible default
};
