// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/Engine.h"
#include "Misc/OutputDeviceNull.h"

AMyGameModeBase::AMyGameModeBase()
{
	Score = 0;
}

void AMyGameModeBase::SetScore(int32 NewScore)
{
	Score = NewScore;
}

int32 AMyGameModeBase::GetScore() const
{
	return Score;
}

void AMyGameModeBase::AddScore(int32 Delta)
{
	Score += Delta;
}

void AMyGameModeBase::CallLevelFunction()
{

    if (UWorld* World = GetWorld())
    {
        ALevelScriptActor* LevelScript = World->GetLevelScriptActor();
        if (LevelScript)
        {
            FOutputDeviceNull OutputDevice;
            LevelScript->CallFunctionByNameWithArguments(TEXT("Create_Win_UI"), OutputDevice, nullptr, true);
        }
    }
}
