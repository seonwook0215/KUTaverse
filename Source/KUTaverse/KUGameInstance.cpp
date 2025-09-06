// Fill out your copyright notice in the Description page of Project Settings.


#include "KUGameInstance.h"
#include "WebSocketsModule.h"
#include "Serialization/JsonReader.h"
#include "KUPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/JsonSerializer.h"
#include "KooWebSocketHandler.h"
#include "MyGameModeBase.h"
#include "Engine/LevelScriptActor.h"
#include "JsonObjectConverter.h"
#include "Components/PointLightComponent.h"
#include "Dom/JsonObject.h"
#include "MultiGameHandler.h"
#include "EngineUtils.h"
#include "Misc/OutputDeviceNull.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Widget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MyUserWidget.h"
#include "TimerManager.h"















TMap<FString, cCharacter> UKUGameInstance::CharacterMap;

bool bIsMatchingWaiting = false;
int count = 0;

void UKUGameInstance::Init()
{
	Super::Init();
	CharacterMap.Empty();
	EquipArr.Add(-1);
	EquipArr.Add(-1);
	EquipArr.Add(-1);
	QuestProgressArr.Add(1);
	QuestProgressArr.Add(0);
	QuestProgressArr.Add(0);
	QuestProgressArr.Add(0);
	QuestProgressArr.Add(0);
	QuestProgressArr.Add(0);
	QuestProgressArr.Add(0);

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		FModuleManager::Get().LoadModule("WebSockets");
	}
	WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://3.37.143.131:8080/map");
	WebSocket_Chat = FWebSocketsModule::Get().CreateWebSocket("wss://kutaverse.xyz/game-service/chat");
	//WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://112.157.82.189:8080/map"); 
	//������ �Ǿ��� ��

	
	WebSocket->OnConnected().AddLambda([]()
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Succesfully connected");
		});
	//������ ���� �ʾ��� ��
	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
		});
	//������ ������ ��
	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
		});
	//�޽����� �޾��� ��
	WebSocket->OnMessage().AddLambda([](const FString& MessageString)
		{
			FString OriginalMessage = MessageString;

			OriginalMessage.RemoveAt(0, 1); // ù ��° �߰�ȣ ����
			OriginalMessage.RemoveAt(OriginalMessage.Len() - 1); // ������ �߰�ȣ ����

			while (OriginalMessage.Len() > 0)
			{
				FString ModifiedString;
				while (OriginalMessage.Len() > 0)
				{
					TCHAR Character = OriginalMessage[0];
					OriginalMessage.RemoveAt(0, 1);
					if (Character == ',' && ModifiedString[ModifiedString.Len() - 1] == '}')
					{
						break;
					}
					ModifiedString += Character;
				}
				ModifiedString.TrimStartAndEndInline(); // ���� ����
				ParseJsonData(ModifiedString);
			}
			
		});
	//�޽����� ������ ��
	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
		{
			
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);
		});

	WebSocket_Chat->OnConnected().AddLambda([]()
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Succesfully connected2");
		});
	//������ ������ ��
	WebSocket_Chat->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
		});
	//�޽����� �޾��� ��
	WebSocket_Chat->OnMessage().AddLambda([this](const FString& MessageString)
		{
			MessageArrived = true;
			SetChatLog(MessageString);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Receive message: " + MessageString);
		});
	//�޽����� ������ ��
	WebSocket_Chat->OnMessageSent().AddLambda([](const FString& MessageString)
		{
			
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);
		});

	WebSocket->Connect();
	WebSocket_Chat->Connect();

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		
		FModuleManager::Get().LoadModule("WebSockets");
	}

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		
		return;
	}

	WebSocketHandler = NewObject<UKooWebSocketHandler>(this);
	WebSocketHandler_Alive = NewObject<UMultiGameHandler>(this);
}

void UKUGameInstance::Shutdown()
{
	

	if (WebSocket && WebSocket->IsConnected())
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField(TEXT("mapRequestType"), TEXT("DELETE"));
		JsonObject->SetStringField(TEXT("userId"), GetUserID());
		JsonObject->SetNumberField(TEXT("positionX"), 0);
		JsonObject->SetNumberField(TEXT("positionY"), 0);
		JsonObject->SetNumberField(TEXT("positionZ"), 0);
		JsonObject->SetNumberField(TEXT("rotationPitch"), 0);
		JsonObject->SetNumberField(TEXT("rotationYaw"), 0);
		JsonObject->SetNumberField(TEXT("rotationRoll"), 0);
		JsonObject->SetNumberField(TEXT("velocityX"), 0);
		JsonObject->SetNumberField(TEXT("velocityY"), 0);
		JsonObject->SetNumberField(TEXT("velocityZ"), 0);
		JsonObject->SetStringField(TEXT("status"), TEXT("STAND"));
		JsonObject->SetNumberField(TEXT("aurora"), EquipArr[0]);
		JsonObject->SetNumberField(TEXT("titleBackground"), EquipArr[1]);
		JsonObject->SetNumberField(TEXT("titleColor"), EquipArr[2]);

		FString JsonString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
		// ������ �ʵ忡 0 ����

			
			WebSocket->Send(JsonString);

			// �޽����� ������ ���� �ణ�� ������ �߰�
			
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				[this]() {
					WebSocket->Close();
					WebSocket_Chat->Close();
					
				},
				0.5f, // ���� �ð� (0.5��)
				false
			);
		
	}
	Super::Shutdown();
}


void UKUGameInstance::ParseJsonData(const FString& JsonData)
{
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonData);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	//// JSON �Ľ� �õ�
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		// JSON ��ü�� �迭 ��������
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		JsonArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));

		// �迭�� ��ȸ�ϸ鼭 �� ��ü �Ľ�
		for (const TSharedPtr<FJsonValue>& JsonValue : JsonArray)
		{
			TSharedPtr<FJsonObject> SubJsonObject = JsonValue->AsObject();

			cCharacter Character;

			Character.UserId = SubJsonObject->GetStringField("userId");
			Character.PositionX = SubJsonObject->GetNumberField("positionX");
			Character.PositionY = SubJsonObject->GetNumberField("positionY");
			Character.PositionZ = SubJsonObject->GetNumberField("positionZ");
			Character.RotationPitch = SubJsonObject->GetNumberField("rotationPitch");
			Character.RotationYaw = SubJsonObject->GetNumberField("rotationYaw");
			Character.RotationRoll = SubJsonObject->GetNumberField("rotationRoll");
			Character.VelocityX = SubJsonObject->GetNumberField("velocityX");
			Character.VelocityY = SubJsonObject->GetNumberField("velocityY");
			Character.VelocityZ = SubJsonObject->GetNumberField("velocityZ");
			Character.Status = SubJsonObject->GetStringField("status");
			Character.Aurora = SubJsonObject->GetNumberField("aurora");
			Character.TitleBackground = SubJsonObject->GetNumberField("titleBackground");
			Character.TitleColor = SubJsonObject->GetNumberField("titleColor");

			cCharacter* ExistingCharacter = CharacterMap.Find(Character.UserId);
			if (ExistingCharacter)
			{
				*ExistingCharacter = Character;
			}
			else
			{
				
				CharacterMap.Add(Character.UserId, Character);
			}
		}
	}
	else
	{

	}
}



void UKUGameInstance::ConnectToWebSocket(const FString& Url, const int a)
{
	
	WebSocket_KUBak = FWebSocketsModule::Get().CreateWebSocket(Url);

	if (!WebSocket_KUBak.IsValid()) {
	
		return;
	}

	

	WebSocket_KUBak->OnConnected().AddLambda([this, a]()
		{
			
			SendInitialMessage(a);

		});

	WebSocket_KUBak->OnConnectionError().AddLambda([](const FString& Error)
		{
			
		});

	WebSocket_KUBak->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			
		});

	WebSocket_KUBak->OnMessage().AddLambda([this](const FString& MessageString)
		{
			HandleReceivedMessage(MessageString);
		});

	WebSocket_KUBak->OnMessageSent().AddLambda([](const FString& MessageString)
		{
		
		});

	WebSocket_KUBak->Connect();
}

void UKUGameInstance::SendInitialMessage(const int a)
{
	FKooGameData InitialData;

	if (a == 1)
	{
		int32 RandomNumber = FMath::RandRange(1000, 9999);// For Test

		StoredUserId = UserID;

		StoredminiGameRequestType = "WAIT";
		InitialData.miniGameRequestType = "WAIT";
		InitialData.roomId = "NULL";
		InitialData.userId = StoredUserId;
		InitialData.interrupt = 0;
		InitialData.score = 0;
		InitialData.actorInfoArray = TArray<FActorInfo>();;

		FString OutputString;
		FJsonObjectConverter::UStructToJsonObjectString(InitialData, OutputString);
		WebSocket_KUBak->Send(OutputString);
	}
	else
	{
		StoredUserId = UserID;

		InitialData.miniGameRequestType = "WAIT";
		InitialData.roomId = StoredRoomId;
		InitialData.userId = StoredUserId;
		InitialData.interrupt = 0;
		InitialData.score = 0;
		InitialData.actorInfoArray = TArray<FActorInfo>();;

		FString OutputString;
		FJsonObjectConverter::UStructToJsonObjectString(InitialData, OutputString);
		WebSocket_KUBak->Send(OutputString);
	}
}

void UKUGameInstance::HandleReceivedMessage(const FString& MessageString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MessageString);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		if (JsonObject->HasField("miniGameRequestType"))
		{
			FString MiniGameRequestType = JsonObject->GetStringField("miniGameRequestType");
			int Interrupt = JsonObject->GetIntegerField("interrupt");

			if (MiniGameRequestType == "RUNNING")
			{
				if (Interrupt == 0) { // actor ����
					UWorld* World = GetWorld();
					if (World)
					{
						// UWorld �̸� ���
						FString WorldName = World->GetName();
						

					}

					if (JsonObject->HasField("actorInfoArray"))
					{
						TArray<TSharedPtr<FJsonValue>> ActorInfoArray = JsonObject->GetArrayField("actorInfoArray");
						UKooWebSocketHandler::RemoveEnemyActors(World);
						for (TSharedPtr<FJsonValue> ActorInfoValue : ActorInfoArray)
						{
							TSharedPtr<FJsonObject> ActorInfoObject = ActorInfoValue->AsObject();
							if (ActorInfoObject.IsValid())
							{
								FActorInfo ActorInfo;

								ActorInfo.level = ActorInfoObject->GetStringField("level");
								ActorInfo.x = ActorInfoObject->GetNumberField("x");
								ActorInfo.z = ActorInfoObject->GetNumberField("z");
								ActorInfo.yaw = ActorInfoObject->GetNumberField("yaw");

								UKooWebSocketHandler::SpawnActorAtLocation(World, ActorInfo);
							}
						}
					}
				}
				if (Interrupt == 1) { // EndLine ���߱�
					UWorld* World = GetWorld();
					if (World) {
						UClass* BP_EndLineClass = LoadObject<UClass>(nullptr, TEXT("/Game/BluePrint/Actors/BP_EndLine.BP_EndLine_C"));
						if (BP_EndLineClass) {
							for (TActorIterator<AActor> It(World, BP_EndLineClass); It; ++It) {
								AActor* EndLineActor = *It;
								if (EndLineActor && EndLineActor->ActorHasTag(TEXT("Mine")))
								{
									// �������Ʈ���� ������ MoveDown_EndLine �Լ��� ȣ���մϴ�.
									FOutputDeviceNull ar;
									EndLineActor->CallFunctionByNameWithArguments(TEXT("MoveDown_EndLine"), ar, nullptr, true); //�α� ar, ���� nullptr
								}
							}
						}
					}
				}
				if (Interrupt == 2) { // ���� Actor ������
					UWorld* World = GetWorld();
					if (World) {
						APlayerController* PlayerController = World->GetFirstPlayerController();
						if (PlayerController) {
							FOutputDeviceNull ar;
							PlayerController->CallFunctionByNameWithArguments(TEXT("SetBlockCount"), ar, nullptr, true);
						}
					}
				}

			}
			else if (MiniGameRequestType == "OVER")
			{
				
				AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
				if (GameMode)
				{
					
					GameMode->CallLevelFunction();
				}
			}
		}
		else
		{
			if (JsonObject->HasField("roomId") && JsonObject->HasField("url"))
			{
				UWorld* World = GetWorld();
				FTimerHandle TimerHandle2;
				StoredRoomId = JsonObject->GetStringField("roomId");
				FString Url = JsonObject->GetStringField("url");
				//ConnectToWebSocket(Url,2);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [this, Url]()
					{
						
						ConnectToWebSocket(Url, 2);

						FString LevelName = "Kongoose"; // �̵��Ϸ��� ���� �̸����� ����
						UGameplayStatics::OpenLevel(this, FName(*LevelName));

					}, 3.0f, false);

				
				WebSocketHandler->StartSendingActorPositions(World);

			}
			else
			{
				
			}
		}
	}
	else
	{
		if (count == 0) count++;
		else
		{
			UWorld* World = GetWorld();
			StoredminiGameRequestType = "RUNNING";
		}
	}
}

void UKUGameInstance::CloseKUBak()
{
	WebSocket_KUBak->Close();
}
void UKUGameInstance::CloseAlive()
{
	WebSocket_Alive->Close();
}
void UKUGameInstance::SetUserID(const FString& NewUserID)
{
	UserID = NewUserID;
}
void UKUGameInstance::SetChatLog(const FString& ChatLog)
{
	UserChat = ChatLog;
}
void UKUGameInstance::SetMessageArrived()
{
	MessageArrived = false;
}
bool UKUGameInstance::GetMessageArrived()
{
	return MessageArrived;
}
void UKUGameInstance::SetUserEmail(const FString& NewUserEmail)
{
	UserEmail = NewUserEmail;
}


FString UKUGameInstance::GetUserID() const
{
	return UserID;
}


FString UKUGameInstance::GetUserEmail() const
{
	return UserEmail;
}

void UKUGameInstance::SetUserNickname(const FString& NewUserNickname)
{
	UserNickname = NewUserNickname;
}

FString UKUGameInstance::GetUserNickname() const
{
	return UserNickname;
}

void UKUGameInstance::SetUserCharacterType(const FString& NewUserCharacterType)
{
	UserCharacterType = NewUserCharacterType;
}

FString UKUGameInstance::GetUserCharacterType() const
{
	return UserCharacterType;
}

void UKUGameInstance::SetUserCurrentMoney(const int& NewUserCurrentMoney)
{
	UserCurrentMoney = NewUserCurrentMoney;
}

int UKUGameInstance::GetUserCurrentMoney() const
{
	return UserCurrentMoney;
}

FString UKUGameInstance::GetChatlog()
{
	return UserChat;
}

void UKUGameInstance::SetErrorMessage(const FString& EM)
{
	ErrorMessage = EM;
}

FString UKUGameInstance::GetErrorMessage()
{
	return ErrorMessage;
}

TArray<int> UKUGameInstance::GetInventoryArr()
{
	return InventoryArr;
}

void UKUGameInstance::SetInventoryArr(int num)
{
	if (!InventoryArr.Contains(num))
	{
		InventoryArr.Add(num);
	}
}

TArray<int32> UKUGameInstance::GetEquipArr()
{
	return EquipArr;
}

void UKUGameInstance::SetEquipArr(int number_, int result_)
{
	EquipArr[number_] = result_;
}

TArray<int32> UKUGameInstance::GetQuestProgressArr()
{
	return QuestProgressArr;
}

void UKUGameInstance::SetQuestProgressArr(int number, int result)
{
	QuestProgressArr[number] = result;
}




void UKUGameInstance::ConnectToWebSocket_Alive(const FString& Url, const int a)
{
	
	WebSocket_Alive = FWebSocketsModule::Get().CreateWebSocket("wss://kutaverse.xyz/game-service/taggame");

	if (!WebSocket_Alive.IsValid()) {
		
		return;
	}


	


	WebSocket_Alive->OnConnected().AddLambda([this]()
		{
			
			SendInitialMessage_Alive();
		});


	WebSocket_Alive->OnConnectionError().AddLambda([](const FString& Error)
		{
			
		});


	WebSocket_Alive->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			
		});

	//�޽����� �޾��� ��
	WebSocket_Alive->OnMessage().AddLambda([this](const FString& MessageString)
		{
			
			HandleReceivedMessage_Alive(MessageString);
		});

	//�޽����� ������ ��
	WebSocket_Alive->OnMessageSent().AddLambda([](const FString& MessageString)
		{
			
			
		});

	WebSocket_Alive->Connect();
}

void UKUGameInstance::SendInitialMessage_Alive()
{
	int32 RandomNumber = FMath::RandRange(1000, 9999);// For Test
	StoredUserId_Alive = UserID; // For Test

	FMatchingMessage InitialData;
	InitialData.tagGameStatus = "TAG_GAME_WAITING_FOR_PLAYERS";
	InitialData.request.userId = StoredUserId_Alive;

	FString OutputString;
	FJsonObjectConverter::UStructToJsonObjectString(InitialData, OutputString);
	WebSocket_Alive->Send(OutputString);
}

void UKUGameInstance::HandleReceivedMessage_Alive(const FString& MessageString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MessageString);

	// JSON �Ľ� �õ�
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		// "roomId", "taggerId", "userObjectNumber" �޽��� ó��
		if (JsonObject->HasField("roomId") && JsonObject->HasField("taggerId") && JsonObject->HasField("userObjectNumber"))
		{
			StoredRoomId_Alive = JsonObject->GetStringField("roomId");
			TaggerId_Alive = JsonObject->GetStringField("taggerId");
			UserObjectNumber_Alive = JsonObject->GetIntegerField("userObjectNumber");


			FString LevelName = "Map_MultiMiniGame";
			UGameplayStatics::OpenLevel(this, FName(*LevelName));
			FTimerHandle TimerHandle_Alive;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Alive, [this]()
				{
					UWorld* World = GetWorld();
					if (StoredUserId_Alive.Equals(TaggerId_Alive))
					{
						UMultiGameHandler::SpawnCharcterTagger(World);
					}
					else
					{
						UMultiGameHandler::SpawnCharcterWithMesh(UserObjectNumber_Alive, World);
					}
				}, 3.0f, false);
			/*
			UWorld* World = GetWorld();
			if (StoredUserId.Equals(TaggerId))
			{
				UMultiGameHandler::SpawnCharcterTagger(World);
			}
			else
			{
				UMultiGameHandler::SpawnCharcterWithMesh(UserObjectNumber, World);
			}*/
		}

		if (JsonObject->HasField("message"))
		{
			FString Message = JsonObject->GetStringField("message");
			
			// �޽��� ������ Ȯ���ϰ� Ư�� ���� ����
			if (Message == "win")
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
			else
			{
				
				if (UWorld* World = GetWorld())
				{
					ALevelScriptActor* LevelScript = World->GetLevelScriptActor();
					if (LevelScript)
					{
						FOutputDeviceNull OutputDevice;
						LevelScript->CallFunctionByNameWithArguments(TEXT("Create_Lose_UI"), OutputDevice, nullptr, true);
					}
				}
			}
		}
	}

	else
	{
		// JSON �Ľ� ���� �� �迭�� ó�� �õ�
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> ArrayReader = TJsonReaderFactory<>::Create(MessageString);
		

		if (FJsonSerializer::Deserialize(ArrayReader, JsonArray) && JsonArray.Num() > 0)
		{
			for (auto& UserValue : JsonArray)
			{
				TSharedPtr<FJsonObject> UserObject = UserValue->AsObject();
				if (UserObject.IsValid() && UserObject->GetStringField("userId") == StoredUserId_Alive && UserObject->GetStringField("lifeStatus") == "TAGGED" && !IsCatch_Alive)
				{
					
					// IsCatch ������ true�� �����Ͽ� �ߺ� ���� ����
					IsCatch_Alive = true;

					// TaggerId�� ��� ���� ������ Ȯ��
					if (!TaggerId_Alive.IsEmpty())
					{
						// �±׸� ���� ���͵� ��������
						TArray<AActor*> TaggedActors;
						UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(*TaggerId_Alive), TaggedActors);

						AActor* TargetActor = nullptr;
						if (TaggedActors.Num() > 0)
						{
							TargetActor = TaggedActors[0]; // ù ��° ���� ����
							UPointLightComponent* PointLight = TargetActor->FindComponentByClass<UPointLightComponent>();
							if (PointLight)
							{
								PointLight->SetVisibility(true);
							}
							else
							{
								
							}
						}
						else
						{
							
						}

						// �÷��̾� ��Ʈ�ѷ� ��������
						APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
						if (PlayerController && TargetActor)
						{
							AActor* ControlledActor = PlayerController->GetPawn();
							if (ControlledActor)
							{
								ControlledActor->Destroy();
							}
							// ī�޶� ��ȯ
							PlayerController->SetViewTargetWithBlend(TargetActor, 0.5f);
						}
						else
						{
							
						}
					}
					else
					{
						
					}
				}

				if (UserObject.IsValid() && UserObject->GetStringField("userId") != StoredUserId_Alive && UserObject->GetStringField("lifeStatus") == "NOT_TAGGED")
				{
					
					FMovementResponse MoveRes;
					MoveRes.userId = UserObject->GetStringField("userId");
					MoveRes.userObjectNumber = UserObject->GetIntegerField("userObjectNumber");
					MoveRes.positionX = UserObject->GetNumberField("positionX");
					MoveRes.positionY = UserObject->GetNumberField("positionY");
					MoveRes.positionZ = UserObject->GetNumberField("positionZ");
					MoveRes.rotationPitch = UserObject->GetNumberField("rotationPitch");
					MoveRes.rotationYaw = UserObject->GetNumberField("rotationYaw");
					MoveRes.rotationRoll = UserObject->GetNumberField("rotationRoll");

					UWorld* World = GetWorld();
					UMultiGameHandler::SpawnOrUpdateActor(MoveRes, TaggerId_Alive, World);
				}
				if (UserObject.IsValid() && UserObject->GetStringField("userId") != StoredUserId_Alive && UserObject->GetStringField("lifeStatus") == "TAGGED")
				{
					UMultiGameHandler::RemoveTaggedPlayer(UserObject->GetStringField("userId"));
				}
			}
		}
		else
		{
			
			if (UWorld* World = GetWorld())
			{
				
				ALevelScriptActor* LevelScript = World->GetLevelScriptActor();
				if (LevelScript)
				{
					
					FOutputDeviceNull OutputDevice;
					LevelScript->CallFunctionByNameWithArguments(TEXT("Create_Multi_Matching_UI"), OutputDevice, nullptr, true);
				}
			}
		}
	}

}