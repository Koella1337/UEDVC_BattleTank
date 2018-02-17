// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *	TankTrack is used to set maximum driving force and to apply forces to the Tank.
 */
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = (Rendering, Cooking, Mobile) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	// Sets a throttle between -1 and +1
	void setThrottle(float throttle);
	
private:
	///Assume 40 tonne Tank, 10m/s² == 1000cm/s² acceleration
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// Max force per track in (UE-)Newtons (kgcm/s²)
	float trackMaxDrivingForce = 40000000;	

};
