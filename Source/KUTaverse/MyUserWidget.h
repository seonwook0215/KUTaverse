// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class KUTAVERSE_API UMyWidgetClass : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))  // 블루프린트에 있는 'GameEndWin'을 바인딩
    UCanvasPanel* GameEndWin;
};
