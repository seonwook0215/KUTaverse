// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KUGameInstance.h"
#include "KUTaverseGameMode.generated.h"

UCLASS(minimalapi)
class AKUTaverseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AKUTaverseGameMode();


	UFUNCTION(BlueprintCallable,Category="UMG_Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	

	
	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	void UseSetUserId(const FString& NewUserID);

	UFUNCTION(BlueprintCallable, Category = "UMG_Game")
	void SetCW(UUserWidget* ChangeWidget);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

		UPROPERTY()
		UUserWidget* CurrentWidget;
};



