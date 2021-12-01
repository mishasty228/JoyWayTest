// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class JOYWAYTEST_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USphereComponent* Collision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Range = 15.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
	float Damage = 11.f;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Meta = (ExposeOnSpawn = true))
	TSubclassOf<AActor> TargetType;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* Movement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IniSpeed = 1500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bBounce = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Bounciness = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GravityScale = 0.0f;

///////Functions
	UFUNCTION(BlueprintCallable)
	void FireInDirection (const FVector& ShootDirection);
};
