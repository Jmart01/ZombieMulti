// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZombieMultiGameMode.h"
#include "ZombieMultiCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZombieMultiGameMode::AZombieMultiGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
