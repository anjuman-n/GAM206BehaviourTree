// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCharacterGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class APlayerCharacterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	APlayerCharacterGameMode();
};



