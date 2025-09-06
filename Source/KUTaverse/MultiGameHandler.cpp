// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiGameHandler.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EngineUtils.h"
#include "JsonObjectConverter.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "KUGameInstance.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "UObject/UnrealType.h"


TMap<FString, AActor*> UMultiGameHandler::PlayerActors;
void UMultiGameHandler::SpawnCharcterTagger(UWorld* World)
{
    FString CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter.BP_TopDownCharacter_C");
    UClass* CharacterClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *CharacterBlueprintPath));
    if (CharacterClass)
    {
        if (World)
        {
            // 맵에 있는 모든 PlayerStart 찾기
            TArray<AActor*> PlayerStarts;
            UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

            // "Tagger" 태그에 맞는 PlayerStart 찾기
            TArray<AActor*> TaggedPlayerStarts;
            for (AActor* PlayerStart : PlayerStarts)
            {
                if (PlayerStart->ActorHasTag(FName("Tagger")))
                {
                    TaggedPlayerStarts.Add(PlayerStart);
                }
            }

            if (TaggedPlayerStarts.Num() > 0)
            {
                // 랜덤하게 하나의 PlayerStart 선택
                int32 RandomIndex = FMath::RandRange(0, TaggedPlayerStarts.Num() - 1);
                AActor* SelectedPlayerStart = TaggedPlayerStarts[RandomIndex];

                // 스폰 위치 및 회전 설정
                FVector SpawnLocation = SelectedPlayerStart->GetActorLocation();
                FRotator SpawnRotation = SelectedPlayerStart->GetActorRotation();

                // 캐릭터 스폰
                AActor* SpawnedCharacter = World->SpawnActor<AActor>(CharacterClass, SpawnLocation, SpawnRotation);

                if (SpawnedCharacter)
                {
                    // 리플렉션을 사용하여 'IsControll' 변수 설정
                    FName VarName = FName(TEXT("IsControll"));
                    FProperty* Property = SpawnedCharacter->GetClass()->FindPropertyByName(VarName);
                    if (Property)
                    {
                        FBoolProperty* BoolProp = CastField<FBoolProperty>(Property);
                        if (BoolProp)
                        {
                            // 값을 true로 설정
                            BoolProp->SetPropertyValue_InContainer(SpawnedCharacter, true);
                        }
                        else
                        {
                            
                        }
                    }
                    else
                    {
                        
                    }
                    FString FunctionName = TEXT("Start_Widget");
                    FName FunctionFName(*FunctionName);

                    UFunction* Function = SpawnedCharacter->FindFunction(FunctionFName);
                    if (Function)
                    {
                        SpawnedCharacter->ProcessEvent(Function, nullptr);
                    }
                    else
                    {
                        
                    }

                    // 플레이어 컨트롤러 가져오기
                    APlayerController* PlayerController = World->GetFirstPlayerController();
                    if (PlayerController)
                    {
                        // 스폰된 캐릭터를 캐스팅하여 컨트롤할 수 있게 설정
                        APawn* SpawnedPawn = Cast<APawn>(SpawnedCharacter);
                        if (SpawnedPawn)
                        {
                            PlayerController->Possess(SpawnedPawn);
                        }
                    }
                    
                }
            }
            else
            {
                
            }
        }
    }
    else
    {
        
    }
}

void UMultiGameHandler::SpawnCharcterWithMesh(int32 UserObjectNumber, UWorld* World)
{
    FString CharacterBlueprintPath;
    // 블루프린트 캐릭터 클래스 로드
    switch (UserObjectNumber)
    {
    case 1:
        CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter1.BP_TopDownCharacter1_C");
        break;
    case 2:
        CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter2.BP_TopDownCharacter2_C");
        break;
    case 3:
        CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter3.BP_TopDownCharacter3_C");
        break;
    case 4:
        CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter4.BP_TopDownCharacter4_C");
        break;
    default:
        
        return;
    }
    UClass* CharacterClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *CharacterBlueprintPath));

    if (!CharacterClass)
    {
        
        return;
    }

    if (World)
    {
        // 맵에 있는 모든 PlayerStart 찾기
        TArray<AActor*> PlayerStarts;
        UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

        // "Run" 태그에 맞는 모든 PlayerStart 찾기
        TArray<AActor*> NoneTaggedPlayerStarts;
        for (AActor* PlayerStart : PlayerStarts)
        {
            if (PlayerStart->ActorHasTag(FName("Run")))
            {
                NoneTaggedPlayerStarts.Add(PlayerStart);
            }
        }

        if (NoneTaggedPlayerStarts.Num() > 0)
        {
            // 랜덤하게 하나의 PlayerStart 선택
            int32 RandomIndex = FMath::RandRange(0, NoneTaggedPlayerStarts.Num() - 1);
            AActor* SelectedPlayerStart = NoneTaggedPlayerStarts[RandomIndex];

            // 스폰 위치 및 회전 설정
            FVector SpawnLocation = SelectedPlayerStart->GetActorLocation();
            FRotator SpawnRotation = SelectedPlayerStart->GetActorRotation();

            // 캐릭터 스폰
            AActor* SpawnedCharacter = World->SpawnActor<AActor>(CharacterClass, SpawnLocation, SpawnRotation);
            if (SpawnedCharacter)
            {
                // 리플렉션을 사용하여 'IsControll' 변수 설정
                FName VarName = FName(TEXT("IsControll"));
                FProperty* Property = SpawnedCharacter->GetClass()->FindPropertyByName(VarName);
                if (Property)
                {
                    FBoolProperty* BoolProp = CastField<FBoolProperty>(Property);
                    if (BoolProp)
                    {
                        // 값을 true로 설정
                        BoolProp->SetPropertyValue_InContainer(SpawnedCharacter, true);
                    }
                    else
                    {
                        
                    }
                }
                else
                {
                    
                }
                
                FString FunctionName = TEXT("Start_Widget");
                FName FunctionFName(*FunctionName);

                UFunction* Function = SpawnedCharacter->FindFunction(FunctionFName);
                if (Function)
                {
                    SpawnedCharacter->ProcessEvent(Function, nullptr);
                }
                else
                {
                    
                }
                
                // 플레이어 컨트롤러가 스폰된 캐릭터를 조종하도록 설정
                APlayerController* PlayerController = World->GetFirstPlayerController();
                if (PlayerController)
                {
                    APawn* SpawnedPawn = Cast<APawn>(SpawnedCharacter);
                    if (SpawnedPawn)
                    {
                        PlayerController->Possess(SpawnedPawn);
                    }
                }
            }
            else
            {
                
            }
        }
        else
        {
            
        }
    }
}

void UMultiGameHandler::SpawnActorAtLocation(const FMovementResponse& FMovementResponse, const FString& TaggerID)
{
    if (GWorld)
    {
        UClass* CharacterClass = nullptr;

        if (TaggerID != FMovementResponse.userId)
        {
            FString CharacterBlueprintPath;
            // 블루프린트 캐릭터 클래스 로드
            switch (FMovementResponse.userObjectNumber)
            {
            case 1:
                CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter1.BP_TopDownCharacter1_C");
                break;
            case 2:
                CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter2.BP_TopDownCharacter2_C");
                break;
            case 3:
                CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter3.BP_TopDownCharacter3_C");
                break;
            case 4:
                CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter4.BP_TopDownCharacter4_C");
                break;
            default:
                
                return;
            }
            CharacterClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *CharacterBlueprintPath));
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Hello Hello.");

        }
        else
        {
            FString CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter.BP_TopDownCharacter_C");
            CharacterClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *CharacterBlueprintPath));
        }
    
        FVector SpawnLocation(FMovementResponse.positionX, FMovementResponse.positionY, FMovementResponse.positionZ);
        FRotator SpawnRotaion(FMovementResponse.rotationPitch, FMovementResponse.rotationYaw, FMovementResponse.rotationRoll);
        FActorSpawnParameters SpawnParams;
        AActor* SpawnedCharacter = GWorld->SpawnActor<AActor>(CharacterClass, SpawnLocation, SpawnRotaion, SpawnParams);
        
        if (SpawnedCharacter)
        {
            // 액터에 태그 추가
            SpawnedCharacter->Tags.Add(FName("Other"));
            SpawnedCharacter->Tags.Add(FName(*FMovementResponse.userId));

         
        }
        else
        {
        
        }
        
    }
}

void UMultiGameHandler::RemoveOtherActors()
{
    if (!GWorld)
    {
        
        return;
    }
    // "Other" 태그를 가진 모든 액터 검색
    TArray<AActor*> ActorsWithOtherTag;
    UGameplayStatics::GetAllActorsWithTag(GWorld, FName("Other"), ActorsWithOtherTag);

    // "Other" 태그가 있는 모든 액터 제거
    for (AActor* Actor : ActorsWithOtherTag)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }
}

void UMultiGameHandler::SendActorPosition(const FMovementRequest& MoveReq)
{
    UWorld* World = GetWorld();
    UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());
    
    FMovingMessage DataToSend;

    DataToSend.tagGameStatus = "TAG_GAME_PLAYING_MOVING";
    DataToSend.request.userId = GameInstance->StoredUserId_Alive;
    DataToSend.request.positionX = MoveReq.positionX;
    DataToSend.request.positionY = MoveReq.positionY;
    DataToSend.request.positionZ = MoveReq.positionZ;
    DataToSend.request.rotationPitch = MoveReq.rotationPitch;
    DataToSend.request.rotationYaw = MoveReq.rotationYaw;
    DataToSend.request.rotationRoll = MoveReq.rotationRoll;

    FString OutputString;
    FJsonObjectConverter::UStructToJsonObjectString(DataToSend, OutputString);
    GameInstance->WebSocket_Alive->Send(OutputString);
}

void UMultiGameHandler::SendCatch(const FString& TaggeredId)
{
    UWorld* World = GetWorld();
    UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());
    
    FTagMessage DataToSend;

    DataToSend.tagGameStatus = "TAG_GAME_TAGGING";
    DataToSend.request.roomId = GameInstance->StoredRoomId_Alive;
    DataToSend.request.taggerId = TaggeredId;
    DataToSend.request.taggedPlayerId = GameInstance->StoredUserId_Alive;

    FString OutputString;
    FJsonObjectConverter::UStructToJsonObjectString(DataToSend, OutputString);
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("taggerId: %s, taggedPlayerId: %s"), *DataToSend.request.taggerId, *DataToSend.request.taggedPlayerId));
    GameInstance->WebSocket_Alive->Send(OutputString);
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + OutputString);
}

UClass* UMultiGameHandler::GetCharacterClass(int32 UserObjectNumber, bool IsTagger)
{
    FString CharacterBlueprintPath;
    if (IsTagger)
    {
        CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter.BP_TopDownCharacter_C");
    }
    else
    {
        switch (UserObjectNumber)
        {
        case 1:
            CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter1.BP_TopDownCharacter1_C");
            break;
        case 2:
            CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter2.BP_TopDownCharacter2_C");
            break;
        case 3:
            CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter3.BP_TopDownCharacter3_C");
            break;
        case 4:
            CharacterBlueprintPath = TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter4.BP_TopDownCharacter4_C");
            break;
        default:
            return nullptr;
        }
    }
    return Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *CharacterBlueprintPath));
}

void UMultiGameHandler::SpawnOrUpdateActor(const FMovementResponse& MoveRes, const FString& TaggerID, UWorld* World)
{
    if (!World) return;

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "SpawnOrUpdateActor");

    UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());

    // 로컬 플레이어와 동일한 userId는 건너뜁니다
    if (MoveRes.userId == GameInstance->StoredUserId_Alive) return;

    // 해당 userId에 대한 액터가 이미 존재하는지 확인
    AActor** FoundActor = PlayerActors.Find(MoveRes.userId);
    
    if (FoundActor && *FoundActor)
    {
        // 기존 액터의 위치와 회전을 업데이트
        (*FoundActor)->SetActorLocation(FVector(MoveRes.positionX, MoveRes.positionY, MoveRes.positionZ));
        (*FoundActor)->SetActorRotation(FRotator(MoveRes.rotationPitch, MoveRes.rotationYaw, MoveRes.rotationRoll));
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "No Spawned Just Move");
    }
    else
    {
        // userObjectNumber와 Tagger 여부에 따라 캐릭터 클래스 결정
        UClass* CharacterClass = GetCharacterClass(MoveRes.userObjectNumber, GameInstance->TaggerId_Alive == MoveRes.userId);
        if (!CharacterClass) return;

        FVector SpawnLocation(MoveRes.positionX, MoveRes.positionY, MoveRes.positionZ);
        FRotator SpawnRotation(MoveRes.rotationPitch, MoveRes.rotationYaw, MoveRes.rotationRoll);

        FActorSpawnParameters SpawnParams;
        AActor* SpawnedActor = World->SpawnActor<AActor>(CharacterClass, SpawnLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor)
        {
            // 맵에 추가
            PlayerActors.Add(MoveRes.userId, SpawnedActor);

            SpawnedActor->Tags.Add(FName("Other"));
            SpawnedActor->Tags.Add(FName(*MoveRes.userId));
            if (GameInstance->TaggerId_Alive != MoveRes.userId) SpawnedActor->Tags.Add(FName(FString::FromInt(MoveRes.userObjectNumber)));
            
            UPointLightComponent* PointLight = SpawnedActor->FindComponentByClass<UPointLightComponent>();
            if (PointLight)
            {
                PointLight->SetVisibility(false);
            }
            //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Character spawned successfully with tag.");
        }
    }
}

void UMultiGameHandler::SendGameEndTaggerWin()
{
    UWorld* World = GetWorld();
    UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());

    FOverMessage DataToSend;
    
    DataToSend.tagGameStatus = "TAG_GAME_END";
    DataToSend.request.roomId = GameInstance->StoredRoomId_Alive;
    DataToSend.request.tagGameResultStatus = "TAGGER_WIN";

    FString OutputString;
    FJsonObjectConverter::UStructToJsonObjectString(DataToSend, OutputString);
    GameInstance->WebSocket_Alive->Send(OutputString);
}

void UMultiGameHandler::SendGameEndPlayerWin()
{
    UWorld* World = GetWorld();
    UKUGameInstance* GameInstance = Cast<UKUGameInstance>(World->GetGameInstance());

    FOverMessage DataToSend;

    DataToSend.tagGameStatus = "TAG_GAME_END";
    DataToSend.request.roomId = GameInstance->StoredRoomId_Alive;
    DataToSend.request.tagGameResultStatus = "PLAYERS_WIN";

    FString OutputString;
    FJsonObjectConverter::UStructToJsonObjectString(DataToSend, OutputString);
    GameInstance->WebSocket_Alive->Send(OutputString);
}

void UMultiGameHandler::RemoveTaggedPlayer(const FString& TaggedID)
{
    if (GWorld)
    {
        // 태그를 가진 액터들 가져오기
        TArray<AActor*> TaggedActors;
        UGameplayStatics::GetAllActorsWithTag(GWorld, FName(*TaggedID), TaggedActors);

        if (TaggedActors.Num() > 0)
        {
            for (AActor* Actor : TaggedActors)
            {
                if (Actor)
                {
                    // 액터 제거
                    Actor->Destroy();
                }
            }

            
        }
        else
        {
            
        }

        // PlayerActors 맵에서 제거 (필요한 경우)
        if (PlayerActors.Contains(TaggedID))
        {
            PlayerActors.Remove(TaggedID);
        }
    }
    else
    {
        
    }
}
