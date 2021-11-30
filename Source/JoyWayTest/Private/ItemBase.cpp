// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "JoyWayTest/JoyWayTestCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
	Sphere->SetSphereRadius(60.f);
	Sphere->SetCollisionProfileName(TEXT("Trigger"));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapBegin);

	ItemStruct = FItemStruct();
	
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, 
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (AJoyWayTestCharacter* PlayerCheck = Cast<AJoyWayTestCharacter>(OtherActor))
	{
		PlayerCheck->GetItem(this);
		Destroy();
	}
	return;
}

