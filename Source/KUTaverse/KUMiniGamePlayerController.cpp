#include "KUMiniGamePlayerController.h"
#include "KUDuckAIController.h"
#include "Camera/CameraActor.h"  // ACameraActor Ŭ���� ��� �߰�
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AKUMiniGamePlayerController::AKUMiniGamePlayerController()
{
    bWasUpPressed = false;
    bWasDownPressed = false;
    bWasLeftPressed = false;
    bWasRightPressed = false;

    PlayerScore = 0;
    ScorePerCorrectInput = 100;
}

void AKUMiniGamePlayerController::BeginPlay()
{
    Super::BeginPlay();

    ControlledDuck2 = Cast<AKUDuckCharacter>(GetPawn());

    // AI�� �÷��̾� ī�޶� �ʱ�ȭ
    //AICameraActor = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
    //PlayerCameraActor = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
}

void AKUMiniGamePlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //AKUDuckAIController* AIController = Cast<AKUDuckAIController>(GetWorld()->GetFirstPlayerController()->GetPawn()->GetController());

    //if (AIController && AIController->ReturnAIActing()) {
        // �÷��̾� �Է� üũ �� ī�޶� ��ȯ
        bool bIsUpPressed = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::W);
        bool bIsDownPressed = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::S);
        bool bIsLeftPressed = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::A);
        bool bIsRightPressed = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::D);

        //SwitchToAIView();  // AI ī�޶�� ��ȯ

        if (bIsUpPressed && !bWasUpPressed)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("UUPP"));
            ChangeDirection(EDirection::UP);
            IncreaseScore();
            //SwitchToPlayerView();  // �÷��̾� ī�޶�� ��ȯ
        }
        else if (bIsDownPressed && !bWasDownPressed)
        {
            // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("DDOOWWNN"));
            ChangeDirection(EDirection::DOWN);
            IncreaseScore();
           // SwitchToPlayerView();
        }
        else if (bIsLeftPressed && !bWasLeftPressed)
        {
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("LLEEFFTT"));
            ChangeDirection(EDirection::LEFT);
            IncreaseScore();
           // SwitchToPlayerView();
        }
        else if (bIsRightPressed && !bWasRightPressed)
        {
            //  GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("RRIIGGHHTT"));
            ChangeDirection(EDirection::RIGHT);
            IncreaseScore();
         //   SwitchToPlayerView();
        }

        // ���� ���� ������Ʈ
        bWasUpPressed = bIsUpPressed;
        bWasDownPressed = bIsDownPressed;
        bWasLeftPressed = bIsLeftPressed;
        bWasRightPressed = bIsRightPressed;
    //}
}

void AKUMiniGamePlayerController::ChangeDirection(EDirection Direction)
{
    if (ControlledDuck2)
    {
        ControlledDuck2->UpdateAnimationDirection(Direction);
    }
}

void AKUMiniGamePlayerController::SwitchToAIView()
{
    if (AICameraActor)
    {
        SetViewTargetWithBlend(AICameraActor, 0.5f);  // AI ī�޶�� ��ȯ
    }
}

void AKUMiniGamePlayerController::SwitchToPlayerView()
{
    if (PlayerCameraActor)
    {
        SetViewTargetWithBlend(PlayerCameraActor, 0.5f);  // �÷��̾� ī�޶�� ��ȯ
    }
}

void AKUMiniGamePlayerController::IncreaseScore()
{
    PlayerScore += ScorePerCorrectInput;
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Score: %d"), PlayerScore));
}
