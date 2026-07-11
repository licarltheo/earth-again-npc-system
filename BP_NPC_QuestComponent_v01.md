# BP_NPC_QuestComponent_v01 - NPC Quest System

## Purpose
Quest integration system for NPCs, supporting quest giving, updates, and completion.

## Properties

### Quest Settings
```cpp
UPROPERTY(EditAnywhere, Category = "Quest")
TArray<FString> AvailableQuestIDs;

UPROPERTY(EditAnywhere, Category = "Quest")
TArray<FString> ActiveQuestIDs;

UPROPERTY(EditAnywhere, Category = "Quest")
TArray<FString> CompletedQuestIDs;

UPROPERTY(EditAnywhere, Category = "Quest")
bool bIsQuestGiver = false;

UPROPERTY(EditAnywhere, Category = "Quest")
float ReputationRequired = 0.5f;

UPROPERTY(EditAnywhere, Category = "Quest")
float ReputationGain = 0.5f;

UPROPERTY(EditAnywhere, Category = "Quest")
float ReputationLoss = -0.5f;
```

### Quest Marker
```cpp
UPROPERTY(EditAnywhere, Category = "Quest")
AActor* QuestMarker;

UPROPERTY(EditAnywhere, Category = "Quest")
TEnumAsByte<EQuestMarkerType> QuestMarkerType;

UPROPERTY(EditAnywhere, Category = "Quest")
FLinearColor QuestMarkerColor;

UPROPERTY(EditAnywhere, Category = "Quest")
FString QuestMarkerText;
```

## Quest Marker Types

```cpp
UENUM(BlueprintType)
enum class EQuestMarkerType : uint8
{
    Arrow UMETA(DisplayName = "Arrow"),
    Circle UMETA(DisplayName = "Circle"),
    Diamond UMETA(DisplayName = "Diamond"),
    Star UMETA(DisplayName = "Star")
};
```

## Functions

### GiveQuest(FString QuestID)
- Check if quest is available
- Check if player has required reputation
- Give quest to player
- Show quest marker
- Update quest widget

### UpdateQuestStep(FString QuestID, int32 StepIndex)
- Update quest step
- Check if quest is complete
- If complete, call CompleteQuest()

### CompleteQuest(FString QuestID)
- Mark quest as complete
- Hide quest marker
- Give quest reward
- Add reputation
- Update quest widget
- Remove from active quests

### ShowQuestMarker()
- Create quest marker actor
- Set marker location
- Set marker color
- Set marker text
- Set marker active

### HideQuestMarker()
- Hide quest marker
- Destroy marker actor

### CheckQuestProgress(FString QuestID)
- Check quest progress
- Update quest step
- Return progress percentage

### GiveQuestReward(FString QuestID)
- Give quest reward
- Add reputation
- Update quest widget
- Notify player

### GetAvailableQuests()
- Return array of available quests
- Filter by reputation requirements

### GetActiveQuests()
- Return array of active quests
- Filter by player progress

### GetCompletedQuests()
- Return array of completed quests
- Filter by player completion

## Quest Marker Logic

### Show Quest Marker
- Only show when NPC is available
- Check CurrentState (not working/sleeping/combat)
- Check if player is in range
- Check if quest is available
- Check if player has required reputation

### Hide Quest Marker
- Hide when NPC is working
- Hide when NPC is sleeping
- Hide when NPC is in combat
- Hide when player is far away
- Hide when quest is complete

## Event Graph

### OnQuestAvailable
1. Add quest to available quests
2. Check if player has required reputation
3. Show quest marker if conditions met

### OnQuestUpdate
1. Update quest step
2. Check if quest is complete
3. If complete, call CompleteQuest()

### OnQuestComplete
1. Hide quest marker
2. Give quest reward
3. Add reputation
4. Update quest widget

### OnQuestFailed
1. Hide quest marker
2. Remove from active quests
3. Notify player

## Notes
- Quest markers must be placed correctly
- Quest rewards must be configured
- Reputation system must be integrated
- Quest widget must be updated
- Quest progress must be tracked

## Dependencies
- UE5.2+ Quest System
- UE5.2+ Quest Widget
- UE5.2+ Reputation System
- BP_NPC_Base_v01

## Version
v01

## Author
Earth Again Team

## Last Updated
2026-07-10