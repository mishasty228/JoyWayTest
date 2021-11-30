// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class JOYWAYTEST_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FItemStruct ItemStruct;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, 
	                           class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult ); 

};
