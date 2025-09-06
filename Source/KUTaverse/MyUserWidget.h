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
    UPROPERTY(meta = (BindWidget))  // �������Ʈ�� �ִ� 'GameEndWin'�� ���ε�
    UCanvasPanel* GameEndWin;
};
