// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KUTAVERSE_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    AMyGameModeBase();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SocketHandler")
    int32 Score;

    UFUNCTION(BlueprintCallable, Category = "SocketHandler")
    void SetScore(int32 NewScore);

    UFUNCTION(BlueprintCallable, Category = "SocketHandler")
    int32 GetScore() const;

    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Delta);

    UFUNCTION(BlueprintCallable, Category = "LevelFunction")
    void CallLevelFunction();
};
