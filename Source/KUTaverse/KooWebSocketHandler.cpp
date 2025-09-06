// Fill out your copyright notice in the Description page of Project Settings.


#include "KooWebSocketHandler.h"
#include "KUGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "JsonObjectConverter.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "MyGameModeBase.h"

/*
void UKooWebSocketHandler::SendSpawnedActorInfo(AActor* SpawnedActor, float LocX)
{
	if(!SpawnedActor) return;

	FVector Location = SpawnedActor->GetActorLocation();
	FString Tag = SpawnedActor->Tags.Num() > 0 ? SpawnedActor->Tags[0].ToString() : "NoTag";

	// 디버그 메시지로 전달된 LocX 값 확인
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Received LocX: %.15f"), LocX));

	FActorInfo ActorInfo;
	ActorInfo.level = Tag;
	ActorInfo.X = Location.X;
	ActorInfo.Z = Location.Z;

	// 디버그 메시지로 ActorInfo 확인
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("ActorInfo - Level: %s, X: %.15f, Z: %.2f"), *Tag, ActorInfo.X, ActorInfo.Z));


	FKooGameData GameData;
	if (GWorld)
	{
		UWebSocketGameInstance* GameInstance = Cast<UWebSocketGameInstance>(GWorld->GetGameInstance());
		if (GameInstance)
		{
			GameData.roomId = GameInstance->StoredRoomId;
			GameData.miniGameRequestType = GameInstance->StoredminiGameRequestType;
			GameData.userId = GameInstance->StoredUserId;
		}
	}
	GameData.interrupt = 0;
	GameData.score = 0;
	GameData.actorInfo = ActorInfo;
	FString OutputString;
	FJsonObjectConverter::UStructToJsonObjectString(GameData, OutputString);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Sending Info: %s"), *OutputString));

	if (GWorld)
	{
		UWebSocketGameInstance* GameInstance = Cast<UWebSocketGameInstance>(GWorld->GetGameInstance());
		if (GameInstance && GameInstance->WebSocket.IsValid())
		{
			GameInstance->WebSocket->Send(OutputString);
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Sending Info: %s"), *OutputString));
}
*/
void UKooWebSocketHandler::SendInfoWithInterruptOne()
{
	UWorld* World = GetWorld();

	if (!World) return;
	
	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());
	if (!GameInstance) return;;
	
	FKooGameData GameData;
	GameData.roomId = GameInstance->StoredRoomId;
	GameData.miniGameRequestType = GameInstance->StoredminiGameRequestType;
	GameData.userId = GameInstance->StoredUserId;
	GameData.interrupt = 1;
	GameData.score = 0;
	GameData.actorInfoArray = TArray<FActorInfo>();

	FString OutputString;
	FJsonObjectConverter::UStructToJsonObjectString(GameData, OutputString);
	GameInstance->WebSocket_KUBak->Send(OutputString);
}

void UKooWebSocketHandler::SendInfoWithInterruptTwo()
{
	UWorld* World = GetWorld();

	if (!World) return;

	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());
	if (!GameInstance) return;;

	FKooGameData GameData;
	GameData.roomId = GameInstance->StoredRoomId;
	GameData.miniGameRequestType = GameInstance->StoredminiGameRequestType;
	GameData.userId = GameInstance->StoredUserId;
	GameData.interrupt = 2;
	GameData.score = 0;
	GameData.actorInfoArray = TArray<FActorInfo>();

	FString OutputString;
	FJsonObjectConverter::UStructToJsonObjectString(GameData, OutputString);
	GameInstance->WebSocket_KUBak->Send(OutputString);
}

void UKooWebSocketHandler::SpawnActorAtLocation(UWorld* World, const FActorInfo& ActorInfo)
{
	if (World)
	{
		FVector Location(ActorInfo.x+1700, 0, ActorInfo.z);
		FRotator Rotation(ActorInfo.yaw, 0, 0);
		
		UClass* ActorClass = nullptr;

		if (ActorInfo.level == "Level1")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level01.BP_KOO_Level01_C"));
		}
		else if (ActorInfo.level == "Level2")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level02.BP_KOO_Level02_C"));
		}
		else if (ActorInfo.level == "Level3")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level03.BP_KOO_Level03_C"));
		}
		else if (ActorInfo.level == "Level4")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level04.BP_KOO_Level04_C"));
		}
		else if (ActorInfo.level == "Level5")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level05.BP_KOO_Level05_C"));
		}
		else if (ActorInfo.level == "Level6")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level06.BP_KOO_Level06_C"));
		}
		else if (ActorInfo.level == "Level7")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level07.BP_KOO_Level07_C"));
		}
		else if (ActorInfo.level == "Level8")
		{
			ActorClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/BluePrint/Actors/Koo_Level/BP_KOO_Level08.BP_KOO_Level08_C"));
		}


		if (ActorClass)
		{
			FActorSpawnParameters SpawnParams;
			World->SpawnActor<AActor>(ActorClass, Location, Rotation, SpawnParams);
			
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to find Actor class to spawn"));
		}
	}
}

void UKooWebSocketHandler::SendActorPositions()
{
	TArray<FActorInfo> ActorInfoArray;
	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(GWorld->GetGameInstance());

	
	if (!GameInstance)
	{
		
		return;
	}

	AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(GWorld->GetAuthGameMode());
	if (!GameMode)
	{
		
		return;
	}
	

	// GameMode의 score 값 가져오기
	int32 CurrentScore = GameMode->GetScore();
	
	
	if (GWorld)
	{
		for (TActorIterator<AActor> It(GWorld); It; ++It)
		{
			AActor* Actor = *It;
			if (Actor && Actor->ActorHasTag("KOO"))
			{
				float ActorX = Actor->GetActorLocation().X;
				if (ActorX <= 1000)
				{
					FActorInfo ActorInfo;
					ActorInfo.level = Actor->Tags[0].ToString();
					ActorInfo.x = ActorX;
					ActorInfo.z = Actor->GetActorLocation().Z;
					ActorInfo.yaw = Actor->GetActorRotation().Pitch; // Yaw 값만 사용
					ActorInfoArray.Add(ActorInfo);

					
				}
			}
		}
	}

	FKooGameData DataToSend;
	DataToSend.miniGameRequestType = GameInstance->StoredminiGameRequestType;
	DataToSend.roomId = GameInstance->StoredRoomId;
	DataToSend.userId = GameInstance->StoredUserId;
	DataToSend.interrupt = 0;
	DataToSend.score = CurrentScore;
	DataToSend.actorInfoArray = ActorInfoArray;

	FString OutputString;
	FJsonObjectConverter::UStructToJsonObjectString(DataToSend, OutputString);
	GameInstance->WebSocket_KUBak->Send(OutputString);
}

void UKooWebSocketHandler::RemoveEnemyActors(UWorld* World)
{
	if (World)
	{
		TArray<AActor*> ActorsToRemove;
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (Actor && Actor->ActorHasTag("KOO"))
			{
				float ActorX = Actor->GetActorLocation().X;
				if (ActorX > 1000) {
					Actor->Destroy();
				}
			}
		}
	}
}

void UKooWebSocketHandler::StartSendingActorPositions(UWorld* World)
{
	if (World)
	{
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SendActorPositions"));
		World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.035f, true); //0.035
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Started Sending Actor Positions"));
	}
}

void UKooWebSocketHandler::StopSendingActorPositions(UWorld* World)
{
	if (World)
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Stopped Sending Actor Positions"));
	}
}

void UKooWebSocketHandler::SetScore(int32 NewScore)
{
	Score = NewScore;
}

int32 UKooWebSocketHandler::GetScore() const
{
	return Score;
}

void UKooWebSocketHandler::SendGameOver()
{
	UWorld* World = GetWorld();

	if (!World) return;

	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());
	

	if (!GameInstance) return;;
	AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(World->GetAuthGameMode());
	if (!GameMode)
	{
		//UE_LOG(LogTemp, Error, TEXT("GameMode is nullptr"));
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("GameMode is valid"));

	// GameMode의 score 값 가져오기
	int32 CurrentScore = GameMode->GetScore();
	//UE_LOG(LogTemp, Warning, TEXT("CurrentScore: %d"), CurrentScore);

	FKooGameData GameData;
	GameData.roomId = GameInstance->StoredRoomId;
	GameData.miniGameRequestType = "OVER";
	GameData.userId = GameInstance->StoredUserId;
	GameData.interrupt = 0;
	GameData.score = CurrentScore;
	GameData.actorInfoArray = TArray<FActorInfo>();

	FString OutputString;
	FJsonObjectConverter::UStructToJsonObjectString(GameData, OutputString);
	GameInstance->WebSocket_KUBak->Send(OutputString);
}








