// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Logging/LogMacros.h"
#include "NiagaraSystem.h"
#include "Json.h"
#include "KUPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class KUTAVERSE_API AKUPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AKUPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	void StartTick();
	void StopTick();
	void OnTickToggle();
	void UpdateOrSpawnPlayers();
	
	UFUNCTION(BlueprintCallable)
	void SendText(const FString& ChatData);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TSubclassOf<APawn> BP_MalePawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	TSubclassOf<APawn> BP_FemalePawnClass;
	void EndPlayerInfo();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Meshes")
	USkeletalMesh* MaleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Meshes")
	USkeletalMesh* FemaleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Materials")
	UMaterialInterface* MaleOverlay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Materials")
	UMaterialInterface* FemaleOverlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraSystem* NiagaraEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	UNiagaraSystem* NiagaraEffect_P;
	void SendPlayerInfo();
	void UpdateNewPlayer();
	
	void UpdateWorldInfo();

	float TimeAccumulator;
	float TimeAccumulator2;
	TSubclassOf<APawn> PlayerPawnBPClass;

private:
	FTimerHandle SendPlayerInfoHandle;
	void DeletePlayers();
	FString UserID;
	int cnt;

	TArray<uint8> FStringToUint8(const FString& InputString)
	{
		// Convert the FString to UTF-8 encoded string
		FTCHARToUTF8 Converter(*InputString);
		const ANSICHAR* UTF8String = (ANSICHAR*)Converter.Get();

		// Get the length of the UTF-8 encoded string
		int32 UTF8Length = Converter.Length();

		// Create a TArray<uint8> and copy the UTF-8 string into it
		TArray<uint8> Result;
		Result.Append((uint8*)UTF8String, UTF8Length);

		return Result;
	}

};
