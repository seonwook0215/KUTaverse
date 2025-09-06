#pragma once

#include "CoreMinimal.h"
#include "KUDuckCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"  // ACameraActor Ŭ���� ��� �߰�
#include "KUMiniGamePlayerController.generated.h"

UCLASS()
class KUTAVERSE_API AKUMiniGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKUMiniGamePlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void ChangeDirection(EDirection Direction);

	void IncreaseScore();
	int32 PlayerScore;
	int32 ScorePerCorrectInput;

	void SwitchToAIView();
	void SwitchToPlayerView();

	ACameraActor* AICameraActor;  // AI ī�޶� ����
	ACameraActor* PlayerCameraActor;  // �÷��̾� ī�޶� ����

	bool bWasUpPressed;
	bool bWasDownPressed;
	bool bWasLeftPressed;
	bool bWasRightPressed;

	AKUDuckCharacter* ControlledDuck2;
};
