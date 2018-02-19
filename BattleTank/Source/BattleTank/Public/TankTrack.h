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
	UTankTrack();
	virtual void BeginPlay() override;

	/*
	* Sets the throttle that will be used to drive the Tank.
	* If isRotation == true then throttle will be multiplied by the rotationPriorityFactor.
	*/
	void setThrottle(float throttle, bool isRotation = false);
	
private:
	/// Variables
	float currentThrottle = 0;

	/// Properties
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// Max force per track in (UE-)Newtons (kgcm/s^2)
	float trackMaxDrivingForce = 40000000;	///Assume 40 tonne Tank, 10m/s² == 1000cm/s² acceleration

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// Min multiplier for maxDrivingForce
	float minThrottle = -1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// Max multiplier for maxDrivingForce
	float maxThrottle = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	// The factor that throttle is multiplied with if it is being set as a rotation and rotations are prioritized.
	float rotationPriorityFactor = 2.0f;

	///Private functions
	void correctSlipping();
	void driveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hitResult);
};
