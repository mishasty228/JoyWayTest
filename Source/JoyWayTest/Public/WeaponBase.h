// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoType.h"
#include "ItemBase.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class JOYWAYTEST_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EAmmoType> AmmoType = EAmmoType::EAT_HitScan;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 maxAmmoPerReload = 60;
	
};
