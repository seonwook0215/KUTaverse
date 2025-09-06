// Fill out your copyright notice in the Description page of Project Settings.


#include "KUMiniCharacter.h"

// Sets default values
AKUMiniCharacter::AKUMiniCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKUMiniCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKUMiniCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKUMiniCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

