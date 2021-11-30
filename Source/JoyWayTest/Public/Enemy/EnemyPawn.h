// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoType.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

UCLASS()
class JOYWAYTEST_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* StandMesh;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Damage = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Health = 100;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EAmmoType> AmmoType = EAT_None;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
