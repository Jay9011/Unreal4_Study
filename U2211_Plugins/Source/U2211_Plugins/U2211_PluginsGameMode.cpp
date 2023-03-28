// Copyright Epic Games, Inc. All Rights Reserved.

#include "U2211_PluginsGameMode.h"
#include "U2211_PluginsPlayerController.h"
#include "U2211_PluginsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AU2211_PluginsGameMode::AU2211_PluginsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AU2211_PluginsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}