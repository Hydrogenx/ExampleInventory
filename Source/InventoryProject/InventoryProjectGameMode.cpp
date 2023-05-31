// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryProjectGameMode.h"
#include "InventoryProjectCharacter.h"
#include "Core/IP_PlayerController.h"
#include "UObject/ConstructorHelpers.h"

AInventoryProjectGameMode::AInventoryProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = AIP_PlayerController::StaticClass();
	}
}
