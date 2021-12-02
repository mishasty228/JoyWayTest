// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "JoyWayTestCharacter.generated.h"

class AItemBase;

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFire, TEnumAsByte<EAmmoType>, AmmoType);

UCLASS(config=Game)
class AJoyWayTestCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomAim;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCameraAim;

	
	
public:
	AJoyWayTestCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WeaponMesh;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AWeaponBase* CurrentWeapon;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 WeaponIndex = -1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool Aiming = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TSubclassOf<AWeaponBase>> WeaponsAvailable;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<AWeaponBase> WeaponToSpawn;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EAmmoType> AmmoType = EAT_None;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Ammo")
	int32 HitScanAmmo = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Ammo")
	int32 ProjectileAmmo = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Ammo")
	int32 BombAmmo = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Parameters")
	float Health = 100.f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Parameters")
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadWrite)
	bool bReloading = false;

	UPROPERTY(BlueprintReadWrite)
	FString LevelName = "Map1";
	
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(BlueprintReadWrite,BlueprintCallable,BlueprintAssignable)
	FOnFire OnFire;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this,0);

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	void GetItem(AItemBase* Item);

	UFUNCTION(BlueprintCallable)
	void SetWeapon(int32 index);

	UFUNCTION(BlueprintCallable)
	void AddAmmo(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	void GetDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable)
	void Aim();

	UFUNCTION(BlueprintCallable)
	void UnAim();

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void WeaponUp();

	UFUNCTION(BlueprintCallable)
	void WeaponDown();
};





