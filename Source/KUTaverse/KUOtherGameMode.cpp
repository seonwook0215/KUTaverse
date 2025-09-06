// Fill out your copyright notice in the Description page of Project Settings.

#include "KUOtherGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "KUOtherCharacter.h"

AKUOtherGameMode::AKUOtherGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
