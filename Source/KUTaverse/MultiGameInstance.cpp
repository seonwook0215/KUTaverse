//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "MultiGameInstance.h"
//#include "WebSocketsModule.h"
//#include "Serialization/JsonReader.h"
//#include "JsonObjectConverter.h"
//#include "Serialization/JsonSerializer.h"
//#include "Engine/LevelScriptActor.h"
//#include "Dom/JsonObject.h"
//#include "MultiGameHandler.h"
//#include "Components/PointLightComponent.h"
//#include "EngineUtils.h"
//#include "Misc/OutputDeviceNull.h"
//#include "MultiGameHandler.h"
//#include "Kismet/GameplayStatics.h"
//
//void UMultiGameInstance::Init()
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
//    WebSocketHandler = NewObject<UMultiGameHandler>(this);
//
//    //ConnectToWebSocket("wss://kutaverse.xyz/game-service/taggame",1);
//}
//
//void UMultiGameInstance::Shutdown()
//{
//	if (WebSocket->IsConnected()) {
//
//		WebSocket->Close();
//
//	}
//	Super::Shutdown();
//}
//
//void UMultiGameInstance::ConnectToWebSocket_Alive(const FString& Url, const int a)
//{
//    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Creating WebSocket...");
//	WebSocket = FWebSocketsModule::Get().CreateWebSocket("wss://kutaverse.xyz/game-service/taggame");
//
//	if (!WebSocket.IsValid()) {
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Failed to create WebSocket");
//		return;
//	}
//
//
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "WebSocket created successfully");
//
//
//	WebSocket->OnConnected().AddLambda([this]()
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Succesfully connected");
//			SendInitialMessage();
//		});
//
//
//	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Connection error: " + Error);
//		});
//
//
//	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
//		});
//
//	//메시지를 받았을 때
//	WebSocket->OnMessage().AddLambda([this](const FString& MessageString)
//		{
//			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageString);
//			HandleReceivedMessage(MessageString);
//		});
//
//	//메시지를 보냈을 때
//	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
//		{
//			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);
//            UE_LOG(LogTemp, Log, TEXT("Sent message : % s"), *MessageString);
//		});
//
//	WebSocket->Connect();
//}
//
//void UMultiGameInstance::SendInitialMessage()
//{
//	int32 RandomNumber = FMath::RandRange(1000, 9999);// For Test
//	StoredUserId = FString::Printf(TEXT("user%d"), RandomNumber); // For Test
//
//	FMatchingMessage InitialData;
//	InitialData.tagGameStatus = "TAG_GAME_WAITING_FOR_PLAYERS";
//	InitialData.request.userId = StoredUserId;
//
//	FString OutputString;
//	FJsonObjectConverter::UStructToJsonObjectString(InitialData, OutputString);
//	WebSocket->Send(OutputString);
//}
//
//void UMultiGameInstance::HandleReceivedMessage(const FString& MessageString)
//{
//    TSharedPtr<FJsonObject> JsonObject;
//    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MessageString);
//
//    // JSON 파싱 시도
//    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
//    {
//        // "roomId", "taggerId", "userObjectNumber" 메시지 처리
//        if (JsonObject->HasField("roomId") && JsonObject->HasField("taggerId") && JsonObject->HasField("userObjectNumber"))
//        {
//            StoredRoomId = JsonObject->GetStringField("roomId");
//            TaggerId = JsonObject->GetStringField("taggerId");
//            UserObjectNumber = JsonObject->GetIntegerField("userObjectNumber");
//
//            
//            FString LevelName = "Map_MultiMiniGame";
//            UGameplayStatics::OpenLevel(this, FName(*LevelName));
//            FTimerHandle TimerHandle;
//            
//            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
//                {
//                    UWorld* World = GetWorld();
//                    if (StoredUserId.Equals(TaggerId))
//                    {
//                        UMultiGameHandler::SpawnCharcterTagger(World);
//                    }
//                    else
//                    {
//                        UMultiGameHandler::SpawnCharcterWithMesh(UserObjectNumber, World);
//                    }
//                }, 3.0f, false);
//            /*
//            UWorld* World = GetWorld();
//            if (StoredUserId.Equals(TaggerId))
//            {
//                UMultiGameHandler::SpawnCharcterTagger(World);
//            }
//            else
//            {
//                UMultiGameHandler::SpawnCharcterWithMesh(UserObjectNumber, World);
//            }*/
//        }
//
//        if (JsonObject->HasField("message"))
//        {
//            FString Message = JsonObject->GetStringField("message");
//            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageString);
//            // 메시지 내용을 확인하고 특정 동작 수행
//            if (Message == "win")
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Victory! You have won the game.");
//                if (UWorld* World = GetWorld())
//                {
//                    ALevelScriptActor* LevelScript = World->GetLevelScriptActor();
//                    if (LevelScript)
//                    {
//                        FOutputDeviceNull OutputDevice;
//                        LevelScript->CallFunctionByNameWithArguments(TEXT("Create_Win_UI"), OutputDevice, nullptr, true);
//                    }
//                }
//            }
//            else
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Defeat! Better luck next time.");
//                if (UWorld* World = GetWorld())
//                {
//                    ALevelScriptActor* LevelScript = World->GetLevelScriptActor();
//                    if (LevelScript)
//                    {
//                        FOutputDeviceNull OutputDevice;
//                        LevelScript->CallFunctionByNameWithArguments(TEXT("Create_Lose_UI"), OutputDevice, nullptr, true);
//                    }
//                }
//            }
//        }
//    }
//    
//    else
//    {
//        // JSON 파싱 실패 시 배열로 처리 시도
//        TArray<TSharedPtr<FJsonValue>> JsonArray;
//        TSharedRef<TJsonReader<>> ArrayReader = TJsonReaderFactory<>::Create(MessageString);
//        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageString);
//
//        if (FJsonSerializer::Deserialize(ArrayReader, JsonArray) && JsonArray.Num() > 0)
//        {
//            for (auto& UserValue : JsonArray)
//            {
//                TSharedPtr<FJsonObject> UserObject = UserValue->AsObject();
//                if (UserObject.IsValid() && UserObject->GetStringField("userId") == StoredUserId && UserObject->GetStringField("lifeStatus") == "TAGGED" && !IsCatch)
//                {
//                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("잡았다.")));
//                    // IsCatch 변수를 true로 설정하여 중복 실행 방지
//                    IsCatch = true;
//
//                    // TaggerId가 비어 있지 않은지 확인
//                    if (!TaggerId.IsEmpty())
//                    {
//                        // 태그를 가진 액터들 가져오기
//                        TArray<AActor*> TaggedActors;
//                        UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(*TaggerId), TaggedActors);
//
//                        AActor* TargetActor = nullptr;
//                        if (TaggedActors.Num() > 0)
//                        {
//                            TargetActor = TaggedActors[0]; // 첫 번째 액터 선택
//                            UPointLightComponent* PointLight = TargetActor->FindComponentByClass<UPointLightComponent>();
//                            if (PointLight)
//                            {
//                                PointLight->SetVisibility(true);
//                            }
//                            else
//                            {
//                                UE_LOG(LogTemp, Warning, TEXT("TargetActor에서 PointLightComponent를 찾지 못했습니다."));
//                            }
//                        }
//                        else
//                        {
//                            UE_LOG(LogTemp, Warning, TEXT("TaggerId에 해당하는 액터를 찾지 못했습니다."));
//                        }
//
//                        // 플레이어 컨트롤러 가져오기
//                        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//                        if (PlayerController && TargetActor)
//                        {
//                            AActor* ControlledActor = PlayerController->GetPawn();
//                            if (ControlledActor)
//                            {
//                                ControlledActor->Destroy();
//                            }
//                            // 카메라 전환
//                            PlayerController->SetViewTargetWithBlend(TargetActor, 0.5f);
//                        }
//                        else
//                        {
//                            UE_LOG(LogTemp, Warning, TEXT("TargetActor 또는 PlayerController를 찾지 못했습니다."));
//                        }
//                    }
//                    else
//                    {
//                        UE_LOG(LogTemp, Warning, TEXT("TaggerId가 비어 있습니다."));
//                    }
//                }
//
//                if (UserObject.IsValid() && UserObject->GetStringField("userId") != StoredUserId && UserObject->GetStringField("lifeStatus") == "NOT_TAGGED")
//                {
//                    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Array: ");
//                    FMovementResponse MoveRes;
//                    MoveRes.userId = UserObject->GetStringField("userId");
//                    MoveRes.userObjectNumber = UserObject->GetIntegerField("userObjectNumber");
//                    MoveRes.positionX = UserObject->GetNumberField("positionX");
//                    MoveRes.positionY = UserObject->GetNumberField("positionY");
//                    MoveRes.positionZ = UserObject->GetNumberField("positionZ");
//                    MoveRes.rotationPitch = UserObject->GetNumberField("rotationPitch");
//                    MoveRes.rotationYaw = UserObject->GetNumberField("rotationYaw");
//                    MoveRes.rotationRoll = UserObject->GetNumberField("rotationRoll");
//
//                    UWorld* World = GetWorld();
//                    UMultiGameHandler::SpawnOrUpdateActor(MoveRes, TaggerId, World);
//                }
//                if (UserObject.IsValid() && UserObject->GetStringField("userId") != StoredUserId && UserObject->GetStringField("lifeStatus") == "TAGGED")
//                {
//                    UMultiGameHandler::RemoveTaggedPlayer(UserObject->GetStringField("userId"));
//                }
//            }
//        }
//        else
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Waiting for match...");
//            if (UWorld* World = GetWorld())
//            {
//                ALevelScriptActor* LevelScript = World->GetLevelScriptActor();
//                if (LevelScript)
//                {
//                    FOutputDeviceNull OutputDevice;
//                    LevelScript->CallFunctionByNameWithArguments(TEXT("Create_Multi_Matching_UI"), OutputDevice, nullptr, true);
//                }
//            }
//        }
//    }
//    
//}