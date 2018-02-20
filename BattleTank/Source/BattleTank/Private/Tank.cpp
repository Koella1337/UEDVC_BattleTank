// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"

// Sets default values
ATank::ATank() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();

	curHealth = maxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) {
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Min<int32>(damagePoints, curHealth);

	curHealth -= damageToApply;
	if (curHealth <= 0) {
		OnDeath.Broadcast();
	}

	return damageToApply;
}

float ATank::getHealthPercent() const {
	return (float) curHealth / (float) maxHealth;
}