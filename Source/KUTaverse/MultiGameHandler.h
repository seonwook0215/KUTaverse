// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "MultiGameHandler.generated.h"

/**
 * 
 */
UCLASS()
class KUTAVERSE_API UMultiGameHandler : public UObject
{
	GENERATED_BODY()
	
public:

	static TMap<FString, AActor*> PlayerActors;
	/*
	Response
	*/
	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	static void SpawnCharcterTagger(UWorld* World);

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	static void SpawnCharcterWithMesh(int32 UserObjectNumber, UWorld* World);

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	static void SpawnActorAtLocation(const FMovementResponse& FMovementResponse, const FString& TaggerId);

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	static void RemoveOtherActors();

	/*
	Request
	*/
	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	void SendActorPosition(const FMovementRequest& MoveReq);

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	void SendCatch(const FString& TaggeredId);

	static UClass* GetCharacterClass(int32 UserObjectNumber, bool IsTagger);

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	static void SpawnOrUpdateActor(const FMovementResponse& MoveRes, const FString& TaggerID, UWorld* World);

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	void SendGameEndTaggerWin();

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	void SendGameEndPlayerWin();

	UFUNCTION(BlueprintCallable, Category = "MultiGameHandler")
	static void RemoveTaggedPlayer(const FString& TaggedID);

};
