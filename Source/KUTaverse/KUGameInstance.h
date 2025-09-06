// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Json.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "KUGameInstance.generated.h"

class UMultiGameHandler;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FMathcingRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString userId;
};
// 위치와 회전 정보 구조체
USTRUCT(BlueprintType)
struct FMovementResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString userId;

    UPROPERTY(BlueprintReadOnly)
    int userObjectNumber;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float positionX;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float positionY;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float positionZ;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float rotationPitch;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float rotationYaw;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float rotationRoll;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    FString lifeStatus;
};

USTRUCT(BlueprintType)
struct FMovementRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString userId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float positionX;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float positionY;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float positionZ;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float rotationPitch;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float rotationYaw;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    float rotationRoll;
};

// 태그 관련 요청 구조체
USTRUCT(BlueprintType)
struct FTagRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    FString roomId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    FString taggerId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    FString taggedPlayerId;
};

// 게임 결과 요청 구조체
USTRUCT(BlueprintType)
struct FGameEndRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    FString roomId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Request")
    FString tagGameResultStatus;
};

USTRUCT(BlueprintType)
struct FMatchingMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FString tagGameStatus;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FMathcingRequest request;
};

USTRUCT(BlueprintType)
struct FMovingMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FString tagGameStatus;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FMovementRequest request;
};

USTRUCT(BlueprintType)
struct FTagMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FString tagGameStatus;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FTagRequest request;
};

USTRUCT(BlueprintType)
struct FOverMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FString tagGameStatus;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Message")
    FGameEndRequest request;
};

USTRUCT(BlueprintType)
struct FActorInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString level;

    UPROPERTY(BlueprintReadOnly)
    float x;

    UPROPERTY(BlueprintReadOnly)
    float z;

    UPROPERTY(BlueprintReadOnly)
    float yaw;
};


USTRUCT(BlueprintType)
struct FKooGameData {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString miniGameRequestType;

    UPROPERTY(BlueprintReadOnly)
    FString roomId;

    UPROPERTY(BlueprintReadOnly)
    FString userId;

    UPROPERTY(BlueprintReadOnly)
    int interrupt;

    UPROPERTY(BlueprintReadOnly)
    int score;

    UPROPERTY(BlueprintReadOnly)
    TArray<FActorInfo> actorInfoArray;
};

class cCharacter {

 public:
     cCharacter() {};
     ~cCharacter() {};
     FString UserId;

     float PositionX;
     float PositionY;
     float PositionZ;

     float RotationPitch;
     float RotationYaw;
     float RotationRoll;

     float VelocityX;
     float VelocityY;
     float VelocityZ;

     FString Status;
     int Aurora;
     int TitleBackground;
     int TitleColor;
 };


UCLASS()
class KUTAVERSE_API UKUGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    //공학관이 살아있다
    // 
    UFUNCTION(BlueprintCallable, Category = "HideAndSeekWebSocket")
    void ConnectToWebSocket_Alive(const FString& Url, const int a);

    void SendInitialMessage_Alive();
    TSharedPtr<IWebSocket> WebSocket_Alive;
    void HandleReceivedMessage_Alive(const FString& MessageString);
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
    FString StoredUserId_Alive;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
    FString StoredRoomId_Alive;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
    FString TaggerId_Alive;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
    int32 UserObjectNumber_Alive;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HideAndSeekWebSocket")
    bool IsCatch_Alive = false;

    UPROPERTY(BlueprintReadOnly, Category = "HideAndSeekWebSocket")
    UMultiGameHandler* WebSocketHandler_Alive;
    
    //쿠박게임

    /*UFUNCTION(BlueprintCallable, Category = "WebSocket")
    virtual void Shutdown_() override;*/

    UFUNCTION(BlueprintCallable, Category = "WebSocket")
    void ConnectToWebSocket(const FString& Url, const int a);

    void SendInitialMessage(const int a);
    TSharedPtr<IWebSocket> WebSocket_KUBak;
    void HandleReceivedMessage(const FString& MessageString);

    FString StoredRoomId;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebSocket")
    FString StoredUserId;
    FString StoredminiGameRequestType;

    UPROPERTY(BlueprintReadOnly, Category = "WebSocketHandler")
    UKooWebSocketHandler* WebSocketHandler;

    UFUNCTION(BlueprintCallable)
    void CloseKUBak();
    void CloseAlive();
    //기존 게임 인스턴스
	UFUNCTION(BlueprintCallable)
	void SetUserID(const FString& NewUserID);

    UFUNCTION(BlueprintCallable)
    FString GetUserID() const;

    UFUNCTION(BlueprintCallable)
    void SetUserEmail(const FString& NewUserEmail);

    UFUNCTION(BlueprintCallable)
    FString GetUserEmail() const;


    UFUNCTION(BlueprintCallable)
    void SetUserNickname(const FString& NewUserNickname);

    UFUNCTION(BlueprintCallable)
    FString GetUserNickname() const;

    UFUNCTION(BlueprintCallable)
    void SetUserCharacterType(const FString& NewUserCharacterType);

    UFUNCTION(BlueprintCallable)
    FString GetUserCharacterType() const;

    UFUNCTION(BlueprintCallable)
    void SetUserCurrentMoney(const int& NewUserCurrentMoney);

    UFUNCTION(BlueprintCallable)
    int GetUserCurrentMoney() const;

    UFUNCTION(BlueprintCallable)
    FString GetChatlog();

    UFUNCTION(BlueprintCallable)
    void SetErrorMessage(const FString& EM);
    
    

    UFUNCTION(BlueprintCallable)
    FString GetErrorMessage();

    UFUNCTION(BlueprintCallable)
    TArray<int32> GetInventoryArr();
    UFUNCTION(BlueprintCallable)
    void SetInventoryArr(int num);

    UFUNCTION(BlueprintCallable)
    TArray<int32> GetEquipArr();
    UFUNCTION(BlueprintCallable)
    void SetEquipArr(int number_, int result_);

    UFUNCTION(BlueprintCallable)
    TArray<int32> GetQuestProgressArr();
    UFUNCTION(BlueprintCallable)
    void SetQuestProgressArr(int number, int result);

    UFUNCTION(BlueprintCallable)
    void SetChatLog(const FString& ChatLog);

    UFUNCTION(BlueprintCallable)
    void SetMessageArrived();
    UFUNCTION(BlueprintCallable)
    bool GetMessageArrived();

	virtual void Init() override;
	virtual void Shutdown() override;

    TArray<int> InventoryArr;
    TArray<int> EquipArr;
    TArray<int> QuestProgressArr;
	TSharedPtr<IWebSocket> WebSocket;
    TSharedPtr<IWebSocket> WebSocket_Chat;
	static void ParseJsonData(const FString& JsonData);
    


    TMap<FString, cCharacter>& GetCharacterMap() { return CharacterMap; }
private:
    FString ErrorMessage;
    FString UserID;
    FString UserNickname;
    int UserCurrentMoney;
    FString UserCharacterType;
    FString UserEmail;
    FString UserChat;
    FTimerHandle TimerHandle;
    bool MessageArrived = false;

    static TMap<FString, cCharacter> CharacterMap;
    
};
