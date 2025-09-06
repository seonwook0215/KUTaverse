// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KUDuckCharacter.h"
#include "KUMiniGamePlayerController.h"  // �÷��̾� ��Ʈ�ѷ� ����
#include "KUDuckAIController.generated.h"

/**
 *
 */
UCLASS()
class KUTAVERSE_API AKUDuckAIController : public AAIController
{
    GENERATED_BODY()

public:
    AKUDuckAIController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    // AI �ൿ�� �����ϴ� ����
    
    bool ReturnAIActing();
private:
    
    void ChangeDirection();

    
    // AI�� �����ϴ� ĳ����
    AKUDuckCharacter* ControlledDuck;

    // �ִϸ��̼� �� ���� ���� �ð� ���� ������
    float TimeSinceLastChange;
    float TimeSinceLastChange2;
    float ChangeInterval;
    float RestStartInterval;
    float RestEndInterval;
    bool bIsAIActing;
};
