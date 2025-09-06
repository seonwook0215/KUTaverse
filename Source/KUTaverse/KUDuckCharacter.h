// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KUDuckCharacter.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
	IDLE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class KUTAVERSE_API AKUDuckCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKUDuckCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void UpdateAnimationDirection(EDirection NewDirection);

	UFUNCTION(BlueprintCallable)
	void MakeTimeZero();

	UFUNCTION(BlueprintCallable)
	float ReturnTimeZero();

	float TimeChange;


private:
	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimSequence* UpAnimation;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimSequence* DownAnimation;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimSequence* LeftAnimation;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimSequence* RightAnimation;

	UPROPERTY(EditAnywhere, Category = "Animations")
	UAnimSequence* IdleAnimation;

	EDirection CurrentDirection;

	int32 PlayerScore;

	// 최근 애니메이션 방향


};

