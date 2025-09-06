// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KUDuckCharacter.h"
#include "KUMiniGamePlayerController.h"  // 플레이어 컨트롤러 참조
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
    // AI 행동을 추적하는 변수
    
    bool ReturnAIActing();
private:
    
    void ChangeDirection();

    
    // AI가 조종하는 캐릭터
    AKUDuckCharacter* ControlledDuck;

    // 애니메이션 및 상태 변경 시간 추적 변수들
    float TimeSinceLastChange;
    float TimeSinceLastChange2;
    float ChangeInterval;
    float RestStartInterval;
    float RestEndInterval;
    bool bIsAIActing;
};
