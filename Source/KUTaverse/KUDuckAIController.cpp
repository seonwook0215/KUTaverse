#include "KUDuckAIController.h"

AKUDuckAIController::AKUDuckAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    ChangeInterval = 1.0f; // 2초마다 애니메이션 변경
    RestStartInterval = 4.0f;
    RestEndInterval = 6.0f;
    bIsAIActing = false;  // AI가 행동 중인지 확인하는 변수
}

void AKUDuckAIController::BeginPlay()
{
    Super::BeginPlay();
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("AI Start"));
    ControlledDuck = Cast<AKUDuckCharacter>(GetPawn());
    TimeSinceLastChange = 0.0f;
    TimeSinceLastChange2 = 0.0f;

    
}

void AKUDuckAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //if (ControlledDuck)
    //{
    //    TimeSinceLastChange += DeltaTime;
    //    TimeSinceLastChange2 += DeltaTime;
    //    
    //    if (TimeSinceLastChange2 >= RestStartInterval)
    //    {
    //        bIsAIActing = false;

    //        EDirection RestDirection = static_cast<EDirection>(4);
    //        ControlledDuck->UpdateAnimationDirection(RestDirection);

    //        if (TimeSinceLastChange2 >= RestEndInterval)
    //        {
    //            TimeSinceLastChange2 = 0.0f;
    //            TimeSinceLastChange = 0.0f;
    //        }
    //    }
    //    else if (TimeSinceLastChange >= ChangeInterval)
    //    {
    //        bIsAIActing = true;
    //        EDirection RestDirection = static_cast<EDirection>(4);
    //        ControlledDuck->UpdateAnimationDirection(RestDirection);
    //        ChangeDirection();
    //        TimeSinceLastChange = 0.0f;
    //    }
    //}
}

bool AKUDuckAIController::ReturnAIActing()
{
    return bIsAIActing;
}

void AKUDuckAIController::ChangeDirection()
{
    if (ControlledDuck)
    {
        EDirection NewDirection = static_cast<EDirection>(FMath::RandRange(0, 3));
        ControlledDuck->UpdateAnimationDirection(NewDirection);
    }
}

