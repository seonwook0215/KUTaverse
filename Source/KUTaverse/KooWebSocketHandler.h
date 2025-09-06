// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KooWebSocketHandler.generated.h"

/**
 * 
 */
UCLASS()
class KUTAVERSE_API UKooWebSocketHandler : public UObject
{
	GENERATED_BODY()
	
public:

	//UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	//static void SendSpawnedActorInfo(AActor* SpawnedActor, float LocX);

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	void SendInfoWithInterruptOne();

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	void SendInfoWithInterruptTwo();

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	static void SpawnActorAtLocation(UWorld* World, const FActorInfo& ActorInfo);

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	static void SendActorPositions();

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	static void RemoveEnemyActors(UWorld* World);

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	void StartSendingActorPositions(UWorld* World);

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	void StopSendingActorPositions(UWorld* World);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WebSocketHandler")
	int32 Score;

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	void SetScore(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "WebSocketHandler")
	void SendGameOver();

private:
	FTimerHandle TimerHandle;;
};
