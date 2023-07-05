// Copyright Epic Games, Inc. All Rights Reserved.


#include "OG_GameModeBase.h"

#include "Player/OG_PlayerCharacter.h"

AOG_GameModeBase::AOG_GameModeBase()
{
	DefaultPawnClass = AOG_PlayerCharacter::StaticClass();
}
