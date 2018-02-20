// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMesh"));
	ensure(collisionMesh);
	this->SetRootComponent(collisionMesh);
	collisionMesh->SetNotifyRigidBodyCollision(true);
	collisionMesh->SetVisibility(false);

	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ensure(movementComponent);
	movementComponent->bAutoActivate = false;

	launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
	ensure(launchBlast);
	launchBlast->SetupAttachment(RootComponent);

	impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
	ensure(impactBlast);
	impactBlast->SetupAttachment(RootComponent);
	impactBlast->bAutoActivate = false;

	explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
	ensure(explosionForce);
	explosionForce->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	///add event delegates
	collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	impactBlast->OnSystemFinished.AddDynamic(this, &AProjectile::OnImpactParticlesFinished);
}

//Delegate for the CollisionMesh's Blueprint-Event "On Component Hit"
void AProjectile::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hitResult) {
	launchBlast->Deactivate();
	impactBlast->Activate();
	explosionForce->FireImpulse();
	collisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//Delegate for ImplactBlast's Event "On System Finished"
void AProjectile::OnImpactParticlesFinished(UParticleSystemComponent* PSystem) {
	this->Destroy();		//destroy actor when impact particles have finished playing
}

void AProjectile::launchProjectile(float speed) {
	if (!ensure(movementComponent)) return;

	movementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	movementComponent->Activate();
}