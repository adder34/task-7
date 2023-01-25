// Copyright Epic Games, Inc. All Rights Reserved.

#include "Task6GameMode.h"
#include "Task6Character.h"
#include "UObject/ConstructorHelpers.h"

ATask6GameMode::ATask6GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
