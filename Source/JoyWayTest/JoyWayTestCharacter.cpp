// Copyright Epic Games, Inc. All Rights Reserved.

#include "JoyWayTestCharacter.h"

#include <basetyps.h>
#include <windowsx.h>

#include "HeadMountedDisplayFunctionLibrary.h"
#include "ItemBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


//////////////////////////////////////////////////////////////////////////
// AJoyWayTestCharacter

AJoyWayTestCharacter::AJoyWayTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(this->GetMesh(), FName("head"));
	CameraBoom->SetRelativeLocation(FVector(0,0,90));
	CameraBoom->SocketOffset.Set(0.f, 60.f, 60.f);
	CameraBoom->TargetArmLength = 200.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoomAim = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomAim"));
	CameraBoomAim->SetupAttachment(this->GetMesh(), FName("head"));
	CameraBoomAim->SetRelativeLocation(FVector(0,0,0));
	CameraBoom->SocketOffset.Set(0.f, 0.f, 10.f);
	CameraBoomAim->TargetArmLength = -40.0f; // The camera follows at this distance behind the character	
	CameraBoomAim->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCameraAim = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraAim"));
	FollowCameraAim->SetupAttachment(CameraBoomAim, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCameraAim->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	WeaponMesh->SetupAttachment(this->GetMesh(), FName("hand_rSocket"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJoyWayTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AJoyWayTestCharacter::Fire );
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AJoyWayTestCharacter::Aim );
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AJoyWayTestCharacter::UnAim );

	PlayerInputComponent->BindAction("WeaponUp",IE_Pressed, this, &AJoyWayTestCharacter::WeaponUp);
	PlayerInputComponent->BindAction("WeaponDown",IE_Pressed, this, &AJoyWayTestCharacter::WeaponDown);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJoyWayTestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJoyWayTestCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJoyWayTestCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJoyWayTestCharacter::LookUpAtRate);

	
	
}

void AJoyWayTestCharacter::GetItem(AItemBase* Item)
{
	AWeaponBase* Weapon = Cast<AWeaponBase>(Item);
	if (Weapon)
	{
		WeaponsAvailable.AddUnique(Weapon->GetClass());
		AddAmmo(Weapon);
		SetWeapon(WeaponsAvailable.Num()-1);
		WeaponIndex = WeaponsAvailable.Num()-1;
		//UE_LOG(LogTemp, Display, TEXT("I found an %s"), *Item->ItemStruct.Name);
	}
}

void AJoyWayTestCharacter::SetWeapon(int32 index)
{
	//UE_LOG(LogTemp, Display, TEXT("I found an %s"), *WeaponsAvailable[index].GetDefaultObject()->Mesh->GetStaticMesh()->GetName());
	WeaponMesh->SetStaticMesh(WeaponsAvailable[index].GetDefaultObject()->Mesh->GetStaticMesh());
	AmmoType = WeaponsAvailable[index].GetDefaultObject()->AmmoType;
}

void AJoyWayTestCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJoyWayTestCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJoyWayTestCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AJoyWayTestCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AJoyWayTestCharacter::AddAmmo(AWeaponBase* Weapon)
{
	switch (Weapon->AmmoType)
	{
	case EAT_HitScan:
		HitScanAmmo+=Weapon->maxAmmoPerReload;
		break;
	case EAT_Projectile:
		ProjectileAmmo+=Weapon->maxAmmoPerReload;
		break;
	case EAT_Bombing:
		BombAmmo+=Weapon->maxAmmoPerReload;
		break;
		default:break;
	}
}

void AJoyWayTestCharacter::GetDamage(float Damage)
{
	Health-=Damage;
	if (Health<=0) Die();
}

void AJoyWayTestCharacter::Fire()
{
	//OnFire;
	/*UE_LOG(LogTemp, Display, TEXT("Fire"));
	switch (AmmoType)
	{
	case EAT_HitScan:
		UE_LOG(LogTemp, Display, TEXT("Pew pew hitscan"));
		break;
	case EAT_Projectile:
		UE_LOG(LogTemp, Display, TEXT("Pew pew projectile"));
		break;
	case EAT_Bombing:
		UE_LOG(LogTemp, Display, TEXT("Pew pew bomb"));
		break;
	case EAT_None:
		break;
	default:break;
	}*/
}

void AJoyWayTestCharacter::Aim()
{
	//UE_LOG(LogTemp, Display, TEXT("Aim"));
	FollowCamera->SetActive(false);
	FollowCameraAim->SetActive(true);
	Aiming = true;
	PlayerController->SetViewTargetWithBlend(this, 1.f);
}

void AJoyWayTestCharacter::UnAim()
{
	//UE_LOG(LogTemp, Display, TEXT("UnAim"));
	FollowCameraAim->SetActive(false);
	FollowCamera->SetActive(true);
	Aiming = false;
	PlayerController->SetViewTargetWithBlend(this, 1.f);
}

void AJoyWayTestCharacter::Die()
{
	//UE_LOG(LogTemp,Display,TEXT("Bruh ama dead"));
	this->GetMovementComponent()->StopActiveMovement();
	this->GetMesh()->SetSimulatePhysics(true);
	this->GetMesh()->SetCollisionProfileName("PhysicsActor");
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
		UGameplayStatics::OpenLevel(this, FName(LevelName));
		//this->Destroy();
	}, 3, false);
	
}

void AJoyWayTestCharacter::WeaponUp()
{
	if (WeaponsAvailable.Num()>1)
	{
		if (WeaponIndex<WeaponsAvailable.Num()-1)	WeaponIndex++;
		else WeaponIndex=0;
		SetWeapon(WeaponIndex);
		
	}
}

void AJoyWayTestCharacter::WeaponDown()
{
	if (WeaponsAvailable.Num()>1)
	{
		if (WeaponIndex>0)	WeaponIndex--;
		else WeaponIndex=WeaponsAvailable.Num()-1;
		SetWeapon(WeaponIndex);
		
	}
}
