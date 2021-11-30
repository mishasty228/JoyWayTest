// Copyright Epic Games, Inc. All Rights Reserved.

#include "JoyWayTestGameMode.h"
#include "JoyWayTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJoyWayTestGameMode::AJoyWayTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
