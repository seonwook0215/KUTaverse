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
            // �ʿ� �ִ� ��� PlayerStart ã��
            TArray<AActor*> PlayerStarts;
            UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

            // "Tagger" �±׿� �´� PlayerStart ã��
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
                // �����ϰ� �ϳ��� PlayerStart ����
                int32 RandomIndex = FMath::RandRange(0, TaggedPlayerStarts.Num() - 1);
                AActor* SelectedPlayerStart = TaggedPlayerStarts[RandomIndex];

                // ���� ��ġ �� ȸ�� ����
                FVector SpawnLocation = SelectedPlayerStart->GetActorLocation();
                FRotator SpawnRotation = SelectedPlayerStart->GetActorRotation();

                // ĳ���� ����
                AActor* SpawnedCharacter = World->SpawnActor<AActor>(CharacterClass, SpawnLocation, SpawnRotation);

                if (SpawnedCharacter)
                {
                    // ���÷����� ����Ͽ� 'IsControll' ���� ����
                    FName VarName = FName(TEXT("IsControll"));
                    FProperty* Property = SpawnedCharacter->GetClass()->FindPropertyByName(VarName);
                    if (Property)
                    {
                        FBoolProperty* BoolProp = CastField<FBoolProperty>(Property);
                        if (BoolProp)
                        {
                            // ���� true�� ����
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

                    // �÷��̾� ��Ʈ�ѷ� ��������
                    APlayerController* PlayerController = World->GetFirstPlayerController();
                    if (PlayerController)
                    {
                        // ������ ĳ���͸� ĳ�����Ͽ� ��Ʈ���� �� �ְ� ����
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
    // �������Ʈ ĳ���� Ŭ���� �ε�
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
        // �ʿ� �ִ� ��� PlayerStart ã��
        TArray<AActor*> PlayerStarts;
        UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

        // "Run" �±׿� �´� ��� PlayerStart ã��
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
            // �����ϰ� �ϳ��� PlayerStart ����
            int32 RandomIndex = FMath::RandRange(0, NoneTaggedPlayerStarts.Num() - 1);
            AActor* SelectedPlayerStart = NoneTaggedPlayerStarts[RandomIndex];

            // ���� ��ġ �� ȸ�� ����
            FVector SpawnLocation = SelectedPlayerStart->GetActorLocation();
            FRotator SpawnRotation = SelectedPlayerStart->GetActorRotation();

            // ĳ���� ����
            AActor* SpawnedCharacter = World->SpawnActor<AActor>(CharacterClass, SpawnLocation, SpawnRotation);
            if (SpawnedCharacter)
            {
                // ���÷����� ����Ͽ� 'IsControll' ���� ����
                FName VarName = FName(TEXT("IsControll"));
                FProperty* Property = SpawnedCharacter->GetClass()->FindPropertyByName(VarName);
                if (Property)
                {
                    FBoolProperty* BoolProp = CastField<FBoolProperty>(Property);
                    if (BoolProp)
                    {
                        // ���� true�� ����
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
                
                // �÷��̾� ��Ʈ�ѷ��� ������ ĳ���͸� �����ϵ��� ����
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
            // �������Ʈ ĳ���� Ŭ���� �ε�
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
            // ���Ϳ� �±� �߰�
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
    // "Other" �±׸� ���� ��� ���� �˻�
    TArray<AActor*> ActorsWithOtherTag;
    UGameplayStatics::GetAllActorsWithTag(GWorld, FName("Other"), ActorsWithOtherTag);

    // "Other" �±װ� �ִ� ��� ���� ����
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

    // ���� �÷��̾�� ������ userId�� �ǳʶݴϴ�
    if (MoveRes.userId == GameInstance->StoredUserId_Alive) return;

    // �ش� userId�� ���� ���Ͱ� �̹� �����ϴ��� Ȯ��
    AActor** FoundActor = PlayerActors.Find(MoveRes.userId);
    
    if (FoundActor && *FoundActor)
    {
        // ���� ������ ��ġ�� ȸ���� ������Ʈ
        (*FoundActor)->SetActorLocation(FVector(MoveRes.positionX, MoveRes.positionY, MoveRes.positionZ));
        (*FoundActor)->SetActorRotation(FRotator(MoveRes.rotationPitch, MoveRes.rotationYaw, MoveRes.rotationRoll));
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "No Spawned Just Move");
    }
    else
    {
        // userObjectNumber�� Tagger ���ο� ���� ĳ���� Ŭ���� ����
        UClass* CharacterClass = GetCharacterClass(MoveRes.userObjectNumber, GameInstance->TaggerId_Alive == MoveRes.userId);
        if (!CharacterClass) return;

        FVector SpawnLocation(MoveRes.positionX, MoveRes.positionY, MoveRes.positionZ);
        FRotator SpawnRotation(MoveRes.rotationPitch, MoveRes.rotationYaw, MoveRes.rotationRoll);

        FActorSpawnParameters SpawnParams;
        AActor* SpawnedActor = World->SpawnActor<AActor>(CharacterClass, SpawnLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor)
        {
            // �ʿ� �߰�
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
        // �±׸� ���� ���͵� ��������
        TArray<AActor*> TaggedActors;
        UGameplayStatics::GetAllActorsWithTag(GWorld, FName(*TaggedID), TaggedActors);

        if (TaggedActors.Num() > 0)
        {
            for (AActor* Actor : TaggedActors)
            {
                if (Actor)
                {
                    // ���� ����
                    Actor->Destroy();
                }
            }

            
        }
        else
        {
            
        }

        // PlayerActors �ʿ��� ���� (�ʿ��� ���)
        if (PlayerActors.Contains(TaggedID))
        {
            PlayerActors.Remove(TaggedID);
        }
    }
    else
    {
        
    }
}
