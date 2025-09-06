// Fill out your copyright notice in the Description page of Project Settings.


#include "KUMiniGameRhythmGameMode.h"
#include"KUDuckCharacter.h"
#include"KUMiniGamePlayerController.h"
#include "UObject/ConstructorHelpers.h"

AKUMiniGameRhythmGameMode::AKUMiniGameRhythmGameMode() {

    DefaultPawnClass = AKUDuckCharacter::StaticClass();

    PlayerControllerClass = AKUMiniGamePlayerController::StaticClass();
    //static ConstructorHelpers::FObjectFinder<USoundCue> MusicCueFinder(TEXT("/Game/Audio/MyMusicCue"));
    //if (MusicCueFinder.Succeeded())
    //{
    //    MusicCue = MusicCueFinder.Object;
    //}

    // Other initializations
    //TimeBetweenBeats = 6.0f;  // 6�ʿ� ���ļ� ��Ʈ�� ���
    //BeatInterval = 2.0f;      // �� ��Ʈ ���� (2��)
    //CurrentTime = 0.0f;
    //CurrentBeatIndex = 0;
}