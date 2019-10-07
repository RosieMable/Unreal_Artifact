// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ArtifactGameMode.h"
#include "ArtifactHUD.h"
#include "ArtifactCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArtifactGameMode::AArtifactGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AArtifactHUD::StaticClass();
}
