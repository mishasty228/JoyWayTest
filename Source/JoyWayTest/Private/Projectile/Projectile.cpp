// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->InitSphereRadius(Range);
	Collision->SetupAttachment(Mesh);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	Movement->SetUpdatedComponent(Mesh);
	Movement->InitialSpeed = IniSpeed;
	Movement->MaxSpeed= IniSpeed;
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = bBounce;
	Movement->Bounciness = Bounciness;
	Movement->ProjectileGravityScale =GravityScale;

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Movement->InitialSpeed = IniSpeed;
	Movement->MaxSpeed= IniSpeed;
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = bBounce;
	Movement->Bounciness = Bounciness;
	Movement->ProjectileGravityScale =GravityScale;
	
	Collision->InitSphereRadius(Range);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	Movement->Velocity=ShootDirection*Movement->InitialSpeed;
}

