//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Engine/GameInstance.h"
//#include "IWebSocket.h"
//
//class UKooWebSocketHandler;
//
//#include "WebSocketGameInstance.generated.h"
//
//
///**
// * 
// */
//USTRUCT(BlueprintType)
//struct FActorInfo
//{
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadOnly)
//	FString level;
//
//	UPROPERTY(BlueprintReadOnly)
//	float x;
//
//	UPROPERTY(BlueprintReadOnly)
//	float z;
//
//	UPROPERTY(BlueprintReadOnly) 
//	float yaw;
//}; 
//
//USTRUCT(BlueprintType)
//struct FKooGameData {
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadOnly)
//	FString miniGameRequestType;
//
//	UPROPERTY(BlueprintReadOnly)
//	FString roomId;
//
//	UPROPERTY(BlueprintReadOnly)
//	FString userId;
//
//	UPROPERTY(BlueprintReadOnly)
//	int interrupt;
//
//	UPROPERTY(BlueprintReadOnly)
//	int score;
//
//	UPROPERTY(BlueprintReadOnly)
//	TArray<FActorInfo> actorInfoArray;
//};
//
//
//UCLASS()
//class KUTAVERSE_API UWebSocketGameInstance : public UGameInstance
//{
//	GENERATED_BODY()
//
//public:
//	virtual void Init() override;
//
//	UFUNCTION(BlueprintCallable, Category = "WebSocket")
//	virtual void Shutdown() override;
//
//	UFUNCTION(BlueprintCallable, Category = "WebSocket")
//	void ConnectToWebSocket(const FString& Url, const int a);
//
//	void SendInitialMessage(const int a);
//	TSharedPtr<IWebSocket> WebSocket_KUBak;
//	void HandleReceivedMessage(const FString& MessageString);
//	
//	FString StoredRoomId;
//
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebSocket")
//	FString StoredUserId;
//	
//	FString StoredminiGameRequestType;
//
//	UPROPERTY(BlueprintReadOnly, Category = "WebSocketHandler")
//	UKooWebSocketHandler* WebSocketHandler;
//
//};
