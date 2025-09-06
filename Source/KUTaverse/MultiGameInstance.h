//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Engine/GameInstance.h"
//#include "IWebSocket.h"
//
//class UMultiGameHandler;
//
//#include "MultiGameInstance.generated.h"
//
///**
// * 
// */
//
//USTRUCT(BlueprintType)
//struct FMathcingRequest
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadOnly)
//    FString userId;
//};
//// 위치와 회전 정보 구조체
//USTRUCT(BlueprintType)
//struct FMovementResponse 
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadOnly)
//    FString userId;
//
//    UPROPERTY(BlueprintReadOnly)
//    int userObjectNumber;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float positionX;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float positionY;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float positionZ;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float rotationPitch;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float rotationYaw;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float rotationRoll;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    FString lifeStatus;
//};
//
//USTRUCT(BlueprintType)
//struct FMovementRequest
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadOnly)
//    FString userId;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float positionX;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float positionY;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float positionZ;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float rotationPitch;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float rotationYaw;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    float rotationRoll;
//};
//
//// 태그 관련 요청 구조체
//USTRUCT(BlueprintType)
//struct FTagRequest
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    FString roomId;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    FString taggerId;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    FString taggedPlayerId;
//};
//
//// 게임 결과 요청 구조체
//USTRUCT(BlueprintType)
//struct FGameEndRequest
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    FString roomId;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
//    FString tagGameResultStatus;
//};
//
//USTRUCT(BlueprintType)
//struct FMatchingMessage
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FString tagGameStatus;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FMathcingRequest request;
//};
//
//USTRUCT(BlueprintType)
//struct FMovingMessage
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FString tagGameStatus;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FMovementRequest request;
//};
//
//USTRUCT(BlueprintType)
//struct FTagMessage
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FString tagGameStatus;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FTagRequest request;
//};
//
//USTRUCT(BlueprintType)
//struct FOverMessage
//{
//    GENERATED_BODY()
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FString tagGameStatus;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
//    FGameEndRequest request;
//};
//UCLASS()
//class KUTAVERSE_API UMultiGameInstance : public UGameInstance
//{
//	GENERATED_BODY()
//
//public:
//	virtual void Init() override;
//
//    UFUNCTION(BlueprintCallable, Category = "HideAndSeekWebSocket")
//	virtual void Shutdown() override;
//
//    UFUNCTION(BlueprintCallable, Category = "HideAndSeekWebSocket")
//    void ConnectToWebSocket_Alive(const FString& Url, const int a);
//
//	void SendInitialMessage_Alive();
//	TSharedPtr<IWebSocket> WebSocket_Alive;
//	void HandleReceivedMessage_Alive(const FString& MessageString);
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
//	FString StoredUserId_Alive;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
//    FString StoredRoomId_Alive;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
//    FString TaggerId_Alive;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
//    int32 UserObjectNumber_Alive;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
//    bool IsCatch_Alive = false;
//
//    UPROPERTY(BlueprintReadOnly, Category = "HideAndSeekWebSocket")
//    UMultiGameHandler* WebSocketHandler_Alive;
//};
