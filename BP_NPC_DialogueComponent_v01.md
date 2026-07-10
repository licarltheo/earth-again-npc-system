# BP_NPC_DialogueComponent_v01 - NPC Dialogue System

## Purpose
Reusable dialogue system blueprint for NPC interactions, quests, and reputation.

## Properties

### Components
- **DialogueTree:** Reference to DT_NPC_Dialogue_[NPCName]_v01
- **DialogueHistory:** Array of previous dialogue IDs
- **Reputation:** Float value (0.0 - 1.0)
- **QuestComponent:** Reference to quest system

### Variables
```cpp
UPROPERTY(EditAnywhere, Category = "Dialogue")
TArray<FDialogueNode> DialogueTree;

UPROPERTY(EditAnywhere, Category = "Dialogue")
TArray<FString> DialogueHistory;

UPROPERTY(EditAnywhere, Category = "Dialogue")
float Reputation = 0.5f;

UPROPERTY(EditAnywhere, Category = "Dialogue")
TEnumAsByte<ENPCDialogueState> CurrentState;

UPROPERTY(EditAnywhere, Category = "Dialogue")
FString CurrentDialogueID;

UPROPERTY(EditAnywhere, Category = "Dialogue")
bool bIsQuestGiver = false;

UPROPERTY(EditAnywhere, Category = "Dialogue")
TArray<FString> QuestIDs;

UPROPERTY(EditAnywhere, Category = "Dialogue")
TArray<FString> AvailableQuests;
```

## Dialogue Nodes

```cpp
USTRUCT(BlueprintType)
struct FDialogueNode
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    FString NodeID;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    FString Text;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    TEnumAsByte<ENPCDialogueType> DialogueType;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    TArray<FString> NextNodes;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    bool bIsBranch = false;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    bool bIsQuestStart = false;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    bool bIsQuestUpdate = false;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    bool bIsQuestComplete = false;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    float ReputationChange = 0.0f;
    
    UPROPERTY(EditAnywhere, Category = "Dialogue")
    FString Gesture;
};
```

## Functions

### StartDialogue(FString DialogueID)
- Initialize dialogue with given ID
- Check if player has reputation requirements
- Check if quest is available
- Start dialogue animation

### ProcessDialogue(FString NodeID)
- Process dialogue node
- Update dialogue history
- Update reputation
- Check for quest triggers
- Select next node

### EndDialogue()
- End dialogue animation
- Save dialogue history
- Update quest progress

### UpdateReputation(float Delta)
- Update reputation value
- Clamp between 0.0 and 1.0
- Notify quest system of reputation change

### CheckQuestAvailability(FString QuestID)
- Check if quest is available
- Check if player has required reputation
- Return true/false

### GetAvailableQuests()
- Return array of available quests
- Filter by reputation requirements

## Cultural Tone Rules

### Ghanaian Phrasing
- Use local greetings ("Akwaaba", "Kumasi", etc.)
- Use respectful language for elders
- Use informal language for peers
- Use formal language for authority figures

### Gestures
- Handshake for formal greetings
- Nod for acknowledgment
- Bow for elders
- Wave for casual greetings
- Point for directing attention

### Age-Appropriate Speech
- Children: Simple language, enthusiastic
- Adults: Normal language, professional
- Elders: Respectful language, wisdom

## Quest Marker Logic

### Show Quest Marker
- Only show when NPC is available
- Check CurrentState (not working/sleeping/combat)
- Check if player is in range
- Check if quest is available

### Hide Quest Marker
- Hide when NPC is working
- Hide when NPC is sleeping
- Hide when NPC is in combat
- Hide when player is far away

## Event Graph

### OnDialogueStart
1. Set CurrentState to Dialogue
2. Play greeting animation
3. Show quest marker if applicable

### OnDialogueEnd
1. Set CurrentState to Idle
2. Play idle animation
3. Hide quest marker
4. Save dialogue history

### OnReputationChange
1. Update Reputation variable
2. Check for reputation-based dialogue branches
3. Notify quest system

## Notes
- Dialogue trees must be compiled for each NPC
- Must support branching conversations
- Must remember prior interactions
- Must support quest integration
- Must support reputation influence
- Must support cultural tone rules
- Must support cultural tone rules

## Dependencies
- UE5.2+ Dialogue System
- UE5.2+ Quest System
- UE5.2+ Blackboard System
- BP_NPC_Base_v01
- DT_NPC_Dialogue_[NPCName]_v01

## Version
v01

## Author
Earth Again Team

## Last Updated
2026-07-10