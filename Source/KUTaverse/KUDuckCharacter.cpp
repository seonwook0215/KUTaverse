// Fill out your copyright notice in the Description page of Project Settings.


#include "KUDuckCharacter.h"

// Sets default values
AKUDuckCharacter::AKUDuckCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CurrentDirection = EDirection::IDLE;
    PlayerScore = 0;
    

}

// Called when the game starts or when spawned
void AKUDuckCharacter::BeginPlay()
{
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Character Start"));
	Super::BeginPlay();
	
}

// Called every frame
void AKUDuckCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    TimeChange += DeltaTime;
}

void AKUDuckCharacter::UpdateAnimationDirection(EDirection NewDirection)
{
    if (CurrentDirection != NewDirection)
    {
        CurrentDirection = NewDirection;
        UAnimSequence* AnimationToPlay = nullptr;

        switch (CurrentDirection)
        {
        case EDirection::UP:
            AnimationToPlay = UpAnimation;
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UP"));
            break;
        case EDirection::DOWN:
            AnimationToPlay = DownAnimation;
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("DOWN"));
            break;
        case EDirection::LEFT:
            AnimationToPlay = LeftAnimation;
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("LEFT"));
            break;
        case EDirection::RIGHT:
            AnimationToPlay = RightAnimation;
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("RIGHT"));
            break;
        case EDirection::IDLE:
            AnimationToPlay = IdleAnimation;
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("IDLE"));
            break;
        }

        if (AnimationToPlay)
        {
            // 애니메이션 재생
            if (AnimationToPlay == IdleAnimation) {
                GetMesh()->PlayAnimation(AnimationToPlay, true);
            }
            else {
                GetMesh()->PlayAnimation(AnimationToPlay, false);
            }
        }
    }
}

void AKUDuckCharacter::MakeTimeZero()
{
    TimeChange = 0;
}

float AKUDuckCharacter::ReturnTimeZero()
{
    return TimeChange;
}
