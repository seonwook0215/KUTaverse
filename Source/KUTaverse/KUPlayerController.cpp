// Fill out your copyright notice in the Description page of Project Settings.


#include "KUPlayerController.h"

// Copyright Epic Games, Inc. All Rights Reserved.
#include "KUTaverseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerStart.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "KUGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////////
// AKUTaverseCharacter

AKUPlayerController::AKUPlayerController()
{

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClassFinder(TEXT("/Game/ThirdPerson/Blueprints/BP_OtherCharacter"));
	if (PlayerPawnBPClassFinder.Succeeded())
	{
		PlayerPawnBPClass = PlayerPawnBPClassFinder.Class;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MaleMeshFinder(TEXT("/Game/VRoid_Character/Male/First/SK_VRoid_Test2")); 
	if (MaleMeshFinder.Succeeded())
	{
		MaleMesh = MaleMeshFinder.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FemaleMeshFinder(TEXT("/Game/VRoid_Character/Female/First/SK_VRoid_Test1"));
	if (MaleMeshFinder.Succeeded())
	{
		FemaleMesh = FemaleMeshFinder.Object;
	}
	//static ConstructorHelpers::FClassFinder<APawn> MalePawnBPClass(TEXT("/Game/VRoid_Character/Male/BP_MaleVroidCharacter"));
	//if (MalePawnBPClass.Class != nullptr)
	//{
	//	BP_MalePawnClass = MalePawnBPClass.Class;
	//}

	//static ConstructorHelpers::FClassFinder<APawn> FemalePawnBPClass(TEXT("/Game/VRoid_Character/Female/BP_FemaleVroidCharacter"));
	//if (FemalePawnBPClass.Class != nullptr)
	//{
	//	BP_FemalePawnClass = FemalePawnBPClass.Class;
	//}

	TimeAccumulator = 0.0f;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	cnt = 0;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}


void AKUPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimeAccumulator += DeltaSeconds;
	if (TimeAccumulator >= 0.05f)
	{
		TimeAccumulator = 0.0f;
	}
	
	UpdateOrSpawnPlayers();
}

void AKUPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SendPlayerInfoHandle, this, &AKUPlayerController::SendPlayerInfo, 0.035f, true);
}

void AKUPlayerController::StartTick()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AKUPlayerController::StopTick()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AKUPlayerController::OnTickToggle()
{
	if (PrimaryActorTick.bStartWithTickEnabled)
	{
		StopTick();
	}
	else
	{
		StartTick();
	}
}


void AKUPlayerController::UpdateOrSpawnPlayers()
{
	UWorld* const world = GetWorld();

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UserID = Cast<UKUGameInstance>(GameInstance)->GetUserID();
		TMap<FString, cCharacter>& CharacterMap = Cast<UKUGameInstance>(GameInstance)->GetCharacterMap();

		// 모든 캐릭터 정보 순회
		for (const TPair<FString, cCharacter>& Pair : CharacterMap)
		{
			const FString& OtherUserID = Pair.Key;
			const cCharacter& CharacterInfo = Pair.Value;
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, OtherUserID + "! !" + UserID);

			// 자신의 UserID와 다른 경우
			if (OtherUserID != UserID)
			{

				// 이미 존재하는 플레이어인지 확인
				AKUTaverseCharacter* ExistingPlayer = nullptr;
				for (TActorIterator<AKUTaverseCharacter> It(GetWorld()); It; ++It)
				{
					AKUTaverseCharacter* OtherCharacter = *It;
					if (OtherCharacter->GetName() == OtherUserID)
					{
						ExistingPlayer = OtherCharacter;
						break;
					}
				}


				if (ExistingPlayer)
				{

					FVector CurrentLocation = ExistingPlayer->GetActorLocation();
					FVector TargetLocation(CharacterInfo.PositionX, CharacterInfo.PositionY, CharacterInfo.PositionZ);
					FVector InterpolatedLocation;
					if (CharacterInfo.Status == "STAND") {
						InterpolatedLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), 50.0f);

					}
					else {
						InterpolatedLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), 100.0f);

					}

					FRotator NewRotation(CharacterInfo.RotationPitch, CharacterInfo.RotationYaw, CharacterInfo.RotationRoll);

					ExistingPlayer->SetActorLocation(InterpolatedLocation);
					//ExistingPlayer->SetActorRotation(InterpolatedRotation);
					ExistingPlayer->SetActorRotation(NewRotation);
					// 방향으로 이동
					FVector NewVelocity(CharacterInfo.VelocityX, CharacterInfo.VelocityY, CharacterInfo.VelocityZ);
					ExistingPlayer->AddMovementInput(NewVelocity);
				}
				else
				{
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("spawn"));	
					FVector NewSpawnLocation(CharacterInfo.PositionX, CharacterInfo.PositionY, CharacterInfo.PositionZ);
					FRotator NewSpawnRotation(CharacterInfo.RotationPitch, CharacterInfo.RotationYaw, CharacterInfo.RotationRoll);

					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = nullptr;
					SpawnParams.Name = FName(*OtherUserID);
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

					AKUTaverseCharacter* NewCharacter = world->SpawnActor<AKUTaverseCharacter>(PlayerPawnBPClass, NewSpawnLocation, NewSpawnRotation, SpawnParams);
					NewCharacter->SpawnDefaultController();
					if (NewCharacter)
					{
						
						FString CharacterType = Cast<UKUGameInstance>(GameInstance)->GetUserCharacterType();

						if (CharacterType == "MALE")
						{
							UE_LOG(LogTemp, Display, TEXT("male"));
							NewCharacter->GetMesh()->SetSkeletalMesh(MaleMesh);
							NewCharacter->GetMesh()->SetOverlayMaterial(MaleOverlay);
						}
						else if (CharacterType == "FEMALE")
						{
							UE_LOG(LogTemp, Display, TEXT("female"));
							NewCharacter->GetMesh()->SetSkeletalMesh(FemaleMesh);
							NewCharacter->GetMesh()->SetOverlayMaterial(FemaleOverlay);
						}
						else {
							UE_LOG(LogTemp, Display, TEXT("nothinghappens"));
						}

						UNiagaraComponent* NiagaraComp = NewCharacter->FindComponentByClass<UNiagaraComponent>();
						if (NiagaraComp)
						{
							NiagaraComp->SetAsset(NiagaraEffect);
						}
						UTextRenderComponent* Txt_PlayerName1 = NewCharacter->FindComponentByClass<UTextRenderComponent>();

						if (Txt_PlayerName1)
						{
							Txt_PlayerName1->SetText(FText::FromString(OtherUserID));
							
							Txt_PlayerName1->SetTextRenderColor(FColor::Red); // 빨간색으로 변경
							

						}

						//// 텍스트 및 스프라이트 설정
						//UTextRenderComponent* TextRenderComp = NewCharacter->FindComponentByClass<UTextRenderComponent>();
						//if (TextRenderComp)
						//{
						//	TextRenderComp->SetText(FText::FromString(OtherUserID));
						//}

						//UPaperSpriteComponent* SpriteComp = NewCharacter->FindComponentByClass<UPaperSpriteComponent>();
						//if (SpriteComp)
						//{
						//	SpriteComp->SetSprite(NewSprite);
						//}
						
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Failed to spawn character."));
					}
				

				}
			}
		}

	}
}


void AKUPlayerController::SendText(const FString& ChatData)
{
	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(GetGameInstance());
	if (GameInstance) {
		if (GameInstance->WebSocket_Chat->IsConnected()) {
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Activated"));
			GameInstance->WebSocket_Chat->Send(ChatData);
		}
	}
}


void AKUPlayerController::DeletePlayers()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UserID = Cast<UKUGameInstance>(GameInstance)->GetUserID();
		TMap<FString, cCharacter>& CharacterMap = Cast<UKUGameInstance>(GameInstance)->GetCharacterMap();

		for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
		{
			ACharacter* OtherCharacter = *It;
			const FString& OtherCharacterName = OtherCharacter->GetName();

			// 자신의 캐릭터는 제외
			if (OtherCharacterName != UserID || OtherCharacterName != "NPC_Duck_C_1")
			{

				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, OtherCharacterName);
				// 다른 플레이어 캐릭터인지 확인
				if (!CharacterMap.Contains(OtherCharacterName))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherCharacterName);

					//OtherCharacter->Destroy();
				}
			}
		}
	}
}


void AKUPlayerController::SendPlayerInfo()
{
	cnt++;
	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(GetGameInstance());
	const auto& Player2 = Cast<AKUTaverseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (GameInstance) {
		if (GameInstance->WebSocket->IsConnected()) {
			// Get the character's transform
			if (Player2) {
				FTransform CharacterTransform = Player2->GetActorTransform();
				//auto CharacterTransform2 = GetVelocity();
				// Extract position and rotation from the transform
				FVector CharacterPosition = CharacterTransform.GetTranslation();
				FRotator CharacterRotation = CharacterTransform.Rotator();
				const auto& CharacterVelocity = Player2->GetVelocity();
				// Create a JSON object to hold the data
				TArray<int32>equiparr_ = Cast<UKUGameInstance>(GameInstance)->GetEquipArr();
				TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
				JsonObject->SetStringField(TEXT("mapRequestType"), TEXT("SAVE"));
				JsonObject->SetStringField(TEXT("userId"), GameInstance->GetUserID());
				JsonObject->SetNumberField(TEXT("positionX"), CharacterPosition.X);
				JsonObject->SetNumberField(TEXT("positionY"), CharacterPosition.Y);
				JsonObject->SetNumberField(TEXT("positionZ"), CharacterPosition.Z);
				JsonObject->SetNumberField(TEXT("rotationPitch"), CharacterRotation.Pitch);
				JsonObject->SetNumberField(TEXT("rotationYaw"), CharacterRotation.Yaw);
				JsonObject->SetNumberField(TEXT("rotationRoll"), CharacterRotation.Roll);
				JsonObject->SetNumberField(TEXT("velocityX"), CharacterVelocity.X);
				JsonObject->SetNumberField(TEXT("velocityY"), CharacterVelocity.Y);
				JsonObject->SetNumberField(TEXT("velocityZ"), CharacterVelocity.Z);
				if (Player2->GetCharacterMovement()->IsFalling())
				{
					JsonObject->SetStringField(TEXT("status"), TEXT("JUMP"));  // 점프 중일 때
				}
				else
				{
					JsonObject->SetStringField(TEXT("status"), TEXT("STAND"));  // 점프 중이 아닐 때
				}
				JsonObject->SetNumberField(TEXT("aurora"), equiparr_[0]);
				JsonObject->SetNumberField(TEXT("titleBackground"), equiparr_[1]);
				JsonObject->SetNumberField(TEXT("titleColor"), equiparr_[2]);
				
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("I send it"));
				// Convert the JSON object to a string
				FString JsonString;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
				FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

				TArray<uint8> uint8Arr = FStringToUint8(JsonString);
				// Send the JSON string over the WebSocket
				GameInstance->WebSocket->Send(JsonString);
				//GameInstance->WebSocket->Send(uint8Arr.GetData(), 4096, true);
			}
		}
	}
}


void AKUPlayerController::EndPlayerInfo()
{
	cnt++;
	UKUGameInstance* GameInstance = Cast<UKUGameInstance>(GetGameInstance());
	const auto& Player2 = Cast<AKUTaverseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (GameInstance) {
		if (GameInstance->WebSocket->IsConnected()) {
			// Get the character's transform
			if (Player2) {
				FTransform CharacterTransform = Player2->GetActorTransform();
				//auto CharacterTransform2 = GetVelocity();
				// Extract position and rotation from the transform
				FVector CharacterPosition = CharacterTransform.GetTranslation();
				FRotator CharacterRotation = CharacterTransform.Rotator();
				const auto& CharacterVelocity = Player2->GetVelocity();
				// Create a JSON object to hold the data
				TArray<int32>equiparr_ = Cast<UKUGameInstance>(GameInstance)->GetEquipArr();
				TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
				JsonObject->SetStringField(TEXT("mapRequestType"), TEXT("DELETE"));
				JsonObject->SetStringField(TEXT("userId"), GameInstance->GetUserID());
				JsonObject->SetNumberField(TEXT("positionX"), CharacterPosition.X);
				JsonObject->SetNumberField(TEXT("positionY"), CharacterPosition.Y);
				JsonObject->SetNumberField(TEXT("positionZ"), CharacterPosition.Z);
				JsonObject->SetNumberField(TEXT("rotationPitch"), CharacterRotation.Pitch);
				JsonObject->SetNumberField(TEXT("rotationYaw"), CharacterRotation.Yaw);
				JsonObject->SetNumberField(TEXT("rotationRoll"), CharacterRotation.Roll);
				JsonObject->SetNumberField(TEXT("velocityX"), CharacterVelocity.X);
				JsonObject->SetNumberField(TEXT("velocityY"), CharacterVelocity.Y);
				JsonObject->SetNumberField(TEXT("velocityZ"), CharacterVelocity.Z);
				if (Player2->GetCharacterMovement()->IsFalling())
				{
					JsonObject->SetStringField(TEXT("status"), TEXT("JUMP"));  // 점프 중일 때
				}
				else
				{
					JsonObject->SetStringField(TEXT("status"), TEXT("STAND"));  // 점프 중이 아닐 때
				}
				JsonObject->SetNumberField(TEXT("aurora"), equiparr_[0]);
				JsonObject->SetNumberField(TEXT("titleBackground"), equiparr_[1]);
				JsonObject->SetNumberField(TEXT("titleColor"), equiparr_[2]);

				FString JsonString;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
				FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

				TArray<uint8> uint8Arr = FStringToUint8(JsonString);
				
				GameInstance->WebSocket->Send(JsonString);
				
			}
		}
	}
}


void AKUPlayerController::UpdateWorldInfo()
{
}