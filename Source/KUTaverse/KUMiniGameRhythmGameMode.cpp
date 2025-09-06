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
    //TimeBetweenBeats = 6.0f;  // 6초에 걸쳐서 비트를 재생
    //BeatInterval = 2.0f;      // 각 비트 간격 (2초)
    //CurrentTime = 0.0f;
    //CurrentBeatIndex = 0;
}