# BT_NPC_Shared_v01 - Shared NPC Behavior Tree

## Purpose
Shared behavior tree template usable across all NPC types (family, school, market, gang, government, Circle Foundation).

## Behavior Tree Structure

```
Root
├── Selector [Priority: Danger > Combat > Interaction > Routine > Idle]
│   ├── Sequence [Danger]
│   │   ├── Condition: IsPlayerInDanger?
│   │   ├── Selector [Flee vs Confront]
│   │   │   ├── Sequence [Flee]
│   │   │   │   ├── Action: FleeFromDanger()
│   │   │   │   └── Action: CallForHelp()
│   │   │   └── Sequence [Confront]
│   │   │       ├── Action: ConfrontAggressor()
│   │   │       └── Action: Defend()
│   │   └── Action: SetState(Fleeing)
│   │
│   ├── Sequence [Combat]
│   │   ├── Condition: IsInCombat?
│   │   ├── Action: CombatBehavior()
│   │   └── Action: SetState(Combat)
│   │
│   ├── Sequence [Interaction]
│   │   ├── Condition: IsPlayerInRange?
│   │   ├── Selector [Dialogue vs Quest]
│   │   │   ├── Sequence [Dialogue]
│   │   │   │   ├── Action: StartDialogue()
│   │   │   │   └── Action: ProcessDialogue()
│   │   │   └── Sequence [Quest]
│   │   │       ├── Action: StartQuest()
│   │   │       └── Action: QuestBehavior()
│   │   └── Action: SetState(Interaction)
│   │
│   ├── Sequence [Routine]
│   │   ├── Selector [Daily Routine]
│   │   │   ├── Sequence [Work]
│   │   │   │   ├── Condition: IsWorkingTime?
│   │   │   │   ├── Action: GoToWorkLocation()
│   │   │   │   └── Action: WorkBehavior()
│   │   │   ├── Sequence [School]
│   │   │   │   ├── Condition: IsSchoolTime?
│   │   │   │   ├── Action: GoToSchool()
│   │   │   │   └── Action: SchoolBehavior()
│   │   │   ├── Sequence [Home]
│   │   │   │   ├── Condition: IsHomeTime?
│   │   │   │   ├── Action: GoToHome()
│   │   │   │   └── Action: HomeBehavior()
│   │   │   └── Sequence [Free Time]
│   │   │       ├── Action: FreeTimeBehavior()
│   │   │       └── Action: Idle()
│   │   └── Action: SetState(Routine)
│   │
│   └── Sequence [Idle]
│       ├── Action: IdleBehavior()
│       └── Action: SetState(Idle)
```

## Blackboard Keys

```cpp
// State
UPROPERTY(EditAnywhere, Category = "Blackboard")
TEnumAsByte<ENPCState> CurrentState;

// Player
UPROPERTY(EditAnywhere, Category = "Blackboard")
bool bPlayerInRange;

UPROPERTY(EditAnywhere, Category = "Blackboard")
float PlayerDistance;

UPROPERTY(EditAnywhere, Category = "Blackboard")
bool bPlayerInDanger;

// Location
UPROPERTY(EditAnywhere, Category = "Blackboard")
FVector HomeLocation;

UPROPERTY(EditAnywhere, Category = "Blackboard")
FVector WorkLocation;

UPROPERTY(EditAnywhere, Category = "Blackboard")
FVector SchoolLocation;

// Time
UPROPERTY(EditAnywhere, Category = "Blackboard")
FDateTime CurrentTime;

UPROPERTY(EditAnywhere, Category = "Blackboard")
bool bIsWorkingTime;

UPROPERTY(EditAnywhere, Category = "Blackboard")
bool bIsSchoolTime;

UPROPERTY(EditAnywhere, Category = "Blackboard")
bool bIsHomeTime;

// Quest
UPROPERTY(EditAnywhere, Category = "Blackboard")
bool bHasActiveQuest;

UPROPERTY(EditAnywhere, Category = "Blackboard")
FString ActiveQuestID;

// Reputation
UPROPERTY(EditAnywhere, Category = "Blackboard")
float Reputation;

// Combat
UPROPERTY(EditAnywhere, Category = "Blackboard")
bool bIsInCombat;

UPROPERTY(EditAnywhere, Category = "Blackboard")
AActor* Aggressor;
```

## Behavior Tasks

### IdleBehavior()
- Play idle animation
- Check for player proximity
- Check for dialogue triggers
- Check for danger
- Update blackboard state

### WalkingBehavior()
- Play walk animation
- Move to target location
- Avoid obstacles
- Adjust path around crowds
- Update blackboard state

### WorkBehavior()
- Play work animation
- Perform work tasks
- Check for player interaction
- Check for danger
- Update blackboard state

### SchoolBehavior()
- Play walk animation to school
- Attend classes
- Interact with other students
- Check for player interaction
- Update blackboard state

### HomeBehavior()
- Play walk animation to home
- Rest and recover
- Check for player interaction
- Update blackboard state

### FreeTimeBehavior()
- Play idle animation
- Socialize with other NPCs
- Check for player interaction
- Update blackboard state

### DialogueBehavior()
- Play dialogue animation
- Process dialogue nodes
- Update dialogue history
- Update reputation
- Check for quest triggers
- Update blackboard state

### QuestBehavior()
- Play quest animation
- Complete quest objectives
- Update quest progress
- Check for quest completion
- Update blackboard state

### CombatBehavior()
- Play combat animation
- Attack aggressor
- Defend self
- Call for help if needed
- Update blackboard state

### FleeBehavior()
- Play flee animation
- Run from danger
- Call for help
- Find safe location
- Update blackboard state

### ConfrontBehavior()
- Play confront animation
- Confront aggressor
- Defend self
- Call for help if needed
- Update blackboard state

## Context-Aware Reactions

### Greetings
- Handshake for formal greetings
- Nod for acknowledgment
- Bow for elders
- Wave for casual greetings
- Check player reputation before greeting

### Player Proximity
- Check player distance
- If close, check for dialogue triggers
- If far, resume routine
- Check for danger

### Noise/Conflict
- Detect noise level
- If high, check for danger
- If combat, engage
- If fleeing, flee

### Danger
- Detect danger level
- If high, flee
- If medium, confront
- If low, ignore

### Crowds
- Detect crowd density
- If high, adjust path
- If very high, wait or find alternative route

## Priority Tiers

### Tier 1: Danger
- Highest priority
- Flee from danger
- Call for help
- Confront if necessary

### Tier 2: Combat
- Second highest priority
- Combat behavior
- Defend self
- Call for help

### Tier 3: Interaction
- Third highest priority
- Dialogue with player
- Quest interaction
- Social interaction

### Tier 4: Routine
- Fourth highest priority
- Daily life activities
- Work, school, home
- Free time

### Tier 5: Idle
- Lowest priority
- Idle behavior
- Wait for interactions

## Integration with UE5 Systems

### State Trees
- Compatible with UE5 State Trees
- Use state machine for complex behaviors
- Transition between states based on conditions

### EQS (Environment Query System)
- Use EQS for pathfinding
- Find optimal paths
- Avoid obstacles
- Find safe locations

### Smart Objects
- Use Smart Objects for interactions
- Trigger interactions based on proximity
- Support dynamic interactions

### Locomotion System
- Compatible with main character locomotion
- Use same IK system
- Use same collision system

## Blackboard Value Updates

### OnTick
- Update CurrentTime
- Update PlayerDistance
- Update bPlayerInRange
- Update bIsInCombat

### OnPlayerProximity
- Update bPlayerInRange
- Update PlayerDistance
- Check for greetings
- Check for dialogue triggers

### OnDangerDetected
- Update bPlayerInDanger
- Update bIsInCombat
- Update Aggressor

### OnTimeChange
- Update bIsWorkingTime
- Update bIsSchoolTime
- Update bIsHomeTime
- Update CurrentTime

### OnQuestUpdate
- Update bHasActiveQuest
- Update ActiveQuestID

## Notes
- Behavior tree must be compiled for each NPC type
- Blackboard values must be updated in real-time
- Must support dynamic state changes
- Must support context-aware reactions
- Must support priority-based behavior selection
- Must integrate with existing UE5 systems

## Dependencies
- UE5.2+ Behavior Tree System
- UE5.2+ Blackboard System
- UE5.2+ State Tree System
- UE5.2+ EQS System
- UE5.2+ Smart Objects
- BP_NPC_Base_v01
- BP_NPC_DialogueComponent_v01

## Version
v01

## Author
Earth Again Team

## Last Updated
2026-07-10