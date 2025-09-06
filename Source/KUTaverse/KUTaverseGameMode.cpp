// Copyright Epic Games, Inc. All Rights Reserved.

#include "KUTaverseGameMode.h"
#include "KUTaverseCharacter.h"
#include "KUPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include <Blueprint/UserWidget.h>
#include "Engine/Engine.h"
#include "HAL/IConsoleManager.h"
#include "Misc/App.h"

AKUTaverseGameMode::AKUTaverseGameMode()
{
	//PlayerControllerClass = AKUPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void AKUTaverseGameMode::BeginPlay()
{
	Super::BeginPlay();
	

	//UWorld* World = GetWorld();
	//if (World)
	//{
	//	IConsoleVariable* TickRateVar = IConsoleManager::Get().FindConsoleVariable(TEXT("tick.rate"));
	//	if (TickRateVar)
	//	{
	//		TickRateVar->Set(60.0f);
	//	}
	//}

}
void AKUTaverseGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}




void AKUTaverseGameMode::UseSetUserId(const FString& NewUserID)
{
	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(GetGameInstance());
	GameInstance->SetUserID(NewUserID);
}

void AKUTaverseGameMode::SetCW(UUserWidget* ChangeWidget)
{
	CurrentWidget = ChangeWidget;
}






