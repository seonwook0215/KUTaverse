// // Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "WebSocketGameInstance.h"
//#include "WebSocketsModule.h"
//#include "KUGameInstance.h"
//#include "Serialization/JsonReader.h"
//#include "JsonObjectConverter.h"
//#include "Serialization/JsonSerializer.h"
//#include "Dom/JsonObject.h"
//#include "EngineUtils.h"
//#include "Misc/OutputDeviceNull.h"
//#include "TimerManager.h"
//#include "Blueprint/UserWidget.h"
//#include "Components/CanvasPanel.h"
//#include "MyGameModeBase.h"
//#include "Components/Widget.h"
//#include "Blueprint/WidgetBlueprintLibrary.h"
//#include "Kismet/GameplayStatics.h"
//#include "MyUserWidget.h"
//#include "KooWebSocketHandler.h"
//
//
//bool bIsMatchingWaiting = false;
//int count = 0;
//void UWebSocketGameInstance::Init()
//{
//	Super::Init();
//
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Init Function");
//
//	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "WebSockets module not loaded, loading now...");
//		FModuleManager::Get().LoadModule("WebSockets");
//	}
//
//	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Failed to load WebSockets module");
//		return;
//	}
//
//	WebSocketHandler = NewObject<UKooWebSocketHandler>(this);
//}
//
//void UWebSocketGameInstance::Shutdown()
//{
//	if (WebSocket_KUBak->IsConnected()) {
//
//		WebSocket_KUBak->Close();
//
//	}
//	Super::Shutdown();
//}
//
//void UWebSocketGameInstance::ConnectToWebSocket(const FString& Url, const int a)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Creating WebSocket...");
//	WebSocket_KUBak = FWebSocketsModule::Get().CreateWebSocket(Url);
//
//	if (!WebSocket_KUBak.IsValid()) {
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Failed to create WebSocket");
//		return;
//	}
//
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "WebSocket created successfully");
//
//	WebSocket_KUBak->OnConnected().AddLambda([this, a]()
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully connected");
//			SendInitialMessage(a);
//
//		});
//
//	WebSocket_KUBak->OnConnectionError().AddLambda([](const FString& Error)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Connection error: " + Error);
//		});
//
//	WebSocket_KUBak->OnClosed().AddLambda([this](int32 StatusCode, const FString& Reason, bool bWasClean)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
//		});
//
//	WebSocket_KUBak->OnMessage().AddLambda([this](const FString& MessageString)
//		{
//			HandleReceivedMessage(MessageString);
//		});
//
//	WebSocket_KUBak->OnMessageSent().AddLambda([](const FString& MessageString)
//		{
//			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);
//		});
//
//	WebSocket_KUBak->Connect();
//}
//
//void UWebSocketGameInstance::SendInitialMessage(const int a)
//{
//	FKooGameData InitialData;
//	UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);
//	UKUGameInstance* GameInstance_ = Cast<UKUGameInstance>(World->GetGameInstance());
//	FString UserID_ = Cast<UKUGameInstance>(GameInstance_)->GetUserID();
//	if (a == 1)
//	{
//		int32 RandomNumber = FMath::RandRange(1000, 9999);// For Test
//
//		StoredminiGameRequestType = "WAIT";
//		InitialData.miniGameRequestType = "WAIT";
//		InitialData.roomId = "NULL";
//		InitialData.userId = UserID_;
//		InitialData.interrupt = 0;
//		InitialData.score = 0;
//		InitialData.actorInfoArray = TArray<FActorInfo>();;
//
//		FString OutputString;
//		FJsonObjectConverter::UStructToJsonObjectString(InitialData, OutputString);
//		WebSocket_KUBak->Send(OutputString);
//	}
//	else
//	{
//		InitialData.miniGameRequestType = "WAIT";
//		InitialData.roomId = StoredRoomId;
//		InitialData.userId = UserID_;
//		InitialData.interrupt = 0;
//		InitialData.score = 0;
//		InitialData.actorInfoArray = TArray<FActorInfo>();;
//
//		FString OutputString;
//		FJsonObjectConverter::UStructToJsonObjectString(InitialData, OutputString);
//		WebSocket_KUBak->Send(OutputString);
//	}
//
//}
//
//void UWebSocketGameInstance::HandleReceivedMessage(const FString& MessageString)
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageString);
//	TSharedPtr<FJsonObject> JsonObject;
//	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MessageString);
//
//	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
//	{
//		if (JsonObject->HasField("miniGameRequestType"))
//		{
//			FString MiniGameRequestType = JsonObject->GetStringField("miniGameRequestType");
//			int Interrupt = JsonObject->GetIntegerField("interrupt");
//
//			if (MiniGameRequestType == "RUNNING")
//			{
//				if (Interrupt == 0) { // actor 갱신
//					UWorld* World = GetWorld();
//					if (World)
//					{
//						// UWorld 이름 출력
//						FString WorldName = World->GetName();
//						//UE_LOG(LogTemp, Warning, TEXT("Current World Name: %s"), *WorldName);
//
//						if (GEngine)
//						{
//							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Current World Name: %s"), *WorldName));
//						}
//					}
//					else {
//						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("NO World")));
//					}
//					if (JsonObject->HasField("actorInfoArray"))
//					{
//						TArray<TSharedPtr<FJsonValue>> ActorInfoArray = JsonObject->GetArrayField("actorInfoArray");
//						UKooWebSocketHandler::RemoveEnemyActors(World);
//						for (TSharedPtr<FJsonValue> ActorInfoValue : ActorInfoArray)
//						{
//							TSharedPtr<FJsonObject> ActorInfoObject = ActorInfoValue->AsObject();
//							if (ActorInfoObject.IsValid())
//							{
//								FActorInfo ActorInfo;
//
//								ActorInfo.level = ActorInfoObject->GetStringField("level");
//								ActorInfo.x = ActorInfoObject->GetNumberField("x");
//								ActorInfo.z = ActorInfoObject->GetNumberField("z");
//								ActorInfo.yaw = ActorInfoObject->GetNumberField("yaw");
//
//								UKooWebSocketHandler::SpawnActorAtLocation(World,ActorInfo);
//							}
//						}
//					}
//				}
//				if (Interrupt == 1) { // EndLine 낮추기
//					UWorld* World = GetWorld();
//					if (World) {
//						UClass* BP_EndLineClass = LoadObject<UClass>(nullptr, TEXT("/Game/BluePrint/Actors/BP_EndLine.BP_EndLine_C"));
//						if (BP_EndLineClass) {
//							for (TActorIterator<AActor> It(World, BP_EndLineClass); It; ++It) {
//								AActor* EndLineActor = *It;
//								if (EndLineActor && EndLineActor->ActorHasTag(TEXT("Mine")))
//								{
//									// 블루프린트에서 정의한 MoveDown_EndLine 함수를 호출합니다.
//									FOutputDeviceNull ar;
//									EndLineActor->CallFunctionByNameWithArguments(TEXT("MoveDown_EndLine"), ar, nullptr, true); //로그 ar, 인자 nullptr
//								}
//							}
//						}
//					}
//				}
//				if (Interrupt == 2) { // 다음 Actor 가리기
//					UWorld* World = GetWorld();
//					if (World) {
//						APlayerController* PlayerController = World->GetFirstPlayerController();
//						if (PlayerController) {
//							FOutputDeviceNull ar;
//							PlayerController->CallFunctionByNameWithArguments(TEXT("SetBlockCount"), ar, nullptr, true);
//						}
//					}
//				}
//
//			}
//			else if (MiniGameRequestType == "OVER")
//			{
//				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Conguratulation You Win");
//				AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
//				if (GameMode)
//				{
//					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Conguratulation You Win Win");
//					GameMode->CallLevelFunction();
//				}
//			}
//		}
//		else 
//		{
//			if (JsonObject->HasField("roomId") && JsonObject->HasField("url"))
//			{
//				UWorld* World = GetWorld();
//				FTimerHandle TimerHandle;
//				StoredRoomId = JsonObject->GetStringField("roomId");
//				FString Url = JsonObject->GetStringField("url");
//				//ConnectToWebSocket(Url,2);
//				GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Url]()
//					{
//						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Open: ");
//						ConnectToWebSocket(Url, 2);
//
//						FString LevelName = "Kongoose"; // 이동하려는 레벨 이름으로 변경
//						UGameplayStatics::OpenLevel(this, FName(*LevelName));
//						
//					}, 3.0f, false);
//				
//				WebSocketHandler->StartSendingActorPositions(World);
//				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Parsed roomId: " + StoredRoomId);
//				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Parsed URL: " + Url);
//				
//			}
//			else
//			{
//				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Invalid JSON format. Missing roomId or url.");
//			}
//		}
//	}
//	else 
//	{
//		if (count == 0) count++;
//		else
//		{
//			UWorld* World = GetWorld();
//			StoredminiGameRequestType = "RUNNING";
//		}
//	}
//}
