#pragma once

#include "AmmoType.generated.h"

UENUM(BlueprintType) enum EAmmoType
{
	EAT_HitScan UMETA(DisplayName="Hitscan"),
	EAT_Projectile UMETA(DisplayName="Projectile"),
	EAT_Bombing UMETA(DisplayName="Bomb"),
	EAT_None UMETA(DisplayName="None")
};
