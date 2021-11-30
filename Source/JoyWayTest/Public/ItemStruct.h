#pragma once

#include "ItemStruct.generated.h"

USTRUCT(BlueprintType) struct FItemStruct
{
	GENERATED_BODY();

	FORCEINLINE FItemStruct();
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Amount;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bStackable;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bConsumable;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bEquipable;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UTexture2D* Thumbnail;
	
	
};

inline FItemStruct::FItemStruct(): Thumbnail(nullptr)
{
	Name = "None";
	Amount = 1;
	bStackable = false;
	bConsumable = false;
	bEquipable = false;
}
