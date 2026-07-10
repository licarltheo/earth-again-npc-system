# Earth Again - NPC System Blueprint Outlines

**Internal Dev-Ready | Link Games Studio | Unreal Engine 5.2+**

---

## 📋 Table of Contents

1. [NPC BEHAVIOR & AI](#1-npc-behavior--ai)
2. [NPC DIALOGUE & QUEST INTERACTION](#2-npc-dialogue--quest-interaction)
3. [VISUAL / RIG / ANIMATION SETUP](#3-visual--rig--animation-setup)
4. [SPAWNING & WORLD POPULATION](#4-spawning--world-population)
5. [INTEGRATION & DEV NOTES](#5-integration--dev-notes)

---

## 1. NPC BEHAVIOR & AI

### 1.1 Behavior Tree Template (`BT_NPC_Shared_v01`)

#### Root Structure
```
Selector (Priority)
├── Sequence (Danger Handler)
│   ├── Selector
│   │   ├── Sequence (Flee)
│   │   │   ├── EQS_FindSafeSpot
│   │   │   ├── MoveToSafeSpot
│   │   │   └── PlayAnimation(Flee)
│   │   ├── Sequence (Call for Help)
│   │   │   ├── PlayAnimation(CallForHelp)
│   │   │   └── EQS_FindNearbyNPCs
│   │   └── Sequence (Confront)
│   │       ├── PlayAnimation(Confront)
│   │       └── Blackboard_SetValue(NPC_State, Combat)
│   └── Blackboard_SetValue(NPC_State, Danger)
│
├── Sequence (Interaction Handler)
│   ├── Selector
│   │   ├── Sequence (Dialogue)
│   │   │   ├── EQS_CheckProximityToPlayer
│   │   │   ├── Blackboard_SetValue(NPC_State, Interaction)
│   │   │   ├── PlayAnimation(Greeting)
│   │   │   ├── DialogueComponent.StartDialogue()
│   │   │   └── Wait(DialogueDuration)
│   │   ├── Sequence (Quest)
│   │   │   ├── Blackboard_SetValue(NPC_State, Interaction)
│   │   │   ├── QuestComponent.ShowQuestMarker()
│   │   │   └── Wait(QuestDuration)
│   │   └── Sequence (Greeting)
│   │       ├── Blackboard_SetValue(NPC_State, Interaction)
│   │       ├── PlayAnimation(Greeting)
│   │       └── Wait(GreetingDuration)
│   └── Blackboard_SetValue(NPC_State, Interaction)
│
├── Sequence (Routine Handler)
│   ├── Selector
│   │   ├── Sequence (Work)
│   │   │   ├── Blackboard_GetValue(NPC_DailySchedule)
│   │   │   ├── CheckCurrentTime
│   │   │   ├── MoveToWorkLocation
│   │   │   ├── PlayAnimation(Work)
│   │   │   └── Wait(WorkDuration)
│   │   ├── Sequence (Commute)
│   │   │   ├── Blackboard_GetValue(NPC_DailySchedule)
│   │   │   ├── CheckCurrentTime
│   │   │   ├── MoveToLocation(Home → Work)
│   │   │   └── MoveToLocation(Work → Home)
│   │   ├── Sequence (School)
│   │   │   ├── Blackboard_GetValue(NPC_DailySchedule)
│   │   │   ├── CheckCurrentTime
│   │   │   ├── MoveToLocation(School)
│   │   │   └── PlayAnimation(Study)
│   │   └── Sequence (Home)
│   │       ├── Blackboard_GetValue(NPC_DailySchedule)
│   │       ├── CheckCurrentTime
│   │       ├── MoveToLocation(Home)
│   │       └── PlayAnimation(Idle)
│   └── Blackboard_SetValue(NPC_State, Routine)
│
└── Sequence (Idle Handler)
    ├── Selector
    │   ├── Sequence (Random Idle)
    │   │   ├── RandomFloat(0, 10)
    │   │   ├── Wait(RandomDuration)
    │   │   └── PlayAnimation(Idle)
    │   ├── Sequence (Observation)
    │   │   ├── EQS_CheckProximityToPlayer
    │   │   ├── PlayAnimation(Observation)
    │   │   └── Wait(ObservationDuration)
    │   └── Sequence (Crowd Avoidance)
    │       ├── EQS_FindPathToLocation
    │       ├── MoveToLocation
    │       └── PlayAnimation(Walk)
    └── Blackboard_SetValue(NPC_State, Idle)
```

#### Blackboard Keys
| Key Name | Type | Description |
|----------|------|-------------|
| `NPC_State` | Enum | Current state (Idle, Routine, Interaction, Danger, Combat) |
| `NPC_DailySchedule` | Struct | Time, Activity, Location |
| `NPC_InteractionCooldown` | Float | Cooldown timer |
| `NPC_Reputation` | Float | Reputation score |
| `NPC_IsInteractable` | Boolean | Can interact with player |
| `NPC_QuestActive` | Boolean | Has active quest |
| `NPC_QuestStep` | Integer | Current quest step |
| `NPC_DangerLevel` | Float | Danger level (0-1) |
| `NPC_TargetLocation` | Vector | Target location for movement |
| `NPC_WorkLocation` | Vector | Work location |
| `NPC_HomeLocation` | Vector | Home location |
| `NPC_SchoolLocation` | Vector | School location |

---

### 1.2 EQS Queries

#### EQS_FindSafeSpot (`EQS_NPC_Shared_v01`)
- **Goal**: Find a safe location away from danger
- **Query Steps**:
  1. Get current location
  2. Get danger level from Blackboard
  3. Find locations within radius (1000)
  4. Filter by distance from danger source
  5. Filter by line-of-sight to danger
  6. Return closest safe location

#### EQS_FindInteractionSpot (`EQS_NPC_Shared_v01`)
- **Goal**: Find a suitable location for dialogue
- **Query Steps**:
  1. Get current location
  2. Find locations within radius (500)
  3. Filter by distance from player
  4. Filter by line-of-sight to player
  5. Filter by not in combat
  6. Return closest suitable location

#### EQS_FindPathToLocation (`EQS_NPC_Shared_v01`)
- **Goal**: Find path to target location
- **Query Steps**:
  1. Get current location
  2. Get target location from Blackboard
  3. Find path using NavMesh
  4. Filter by obstacles
  5. Return path points

#### EQS_CheckProximityToPlayer (`EQS_NPC_Shared_v01`)
- **Goal**: Check if player is nearby
- **Query Steps**:
  1. Get current location
  2. Get player location
  3. Calculate distance
  4. Filter by radius (500)
  5. Return proximity result

---

### 1.3 Smart Object Sets

#### Market Stalls (`SO_NPC_Shared_v01`)
- **Tags**: `NPC_Type=Vendor`, `Location=Market`
- **Smart Object Types**:
  - `MarketStall_01` (Auntie Efua)
  - `MarketStall_02` (Other vendors)
- **Activation**: When NPC is in work mode
- **Deactivation**: When NPC is not in work mode

#### School Benches (`SO_NPC_Shared_v01`)
- **Tags**: `NPC_Type=Student`, `Location=School`
- **Smart Object Types**:
  - `SchoolBench_01` (Riverside Primary)
- **Activation**: When NPC is in school mode
- **Deactivation**: When NPC is not in school mode

#### Home Locations (`SO_NPC_Shared_v01`)
- **Tags**: `NPC_Type=Resident`, `Location=Home`
- **Smart Object Types**:
  - `Home_01` (Baba Hassan)
  - `Home_02` (Other residents)
- **Activation**: When NPC is in home mode
- **Deactivation**: When NPC is not in home mode

---

## 2. NPC DIALOGUE & QUEST INTERACTION

### 2.1 Dialogue Component Blueprint (`BP_NPC_DialogueComponent_v01`)

#### Component Structure
```
BP_NPC_DialogueComponent_v01
├── Variables
│   ├── NPCName (String)
│   ├── CurrentDialogue (DT_NPC_Dialogue)
│   ├── CurrentLineIndex (Integer)
│   ├── BranchingChoice (Integer)
│   ├── IsDialogueActive (Boolean)
│   ├── InteractionCooldown (Float)
│   └── Reputation (Float)
│
├── Events
│   ├── InitializeComponent()
│   ├── BeginPlay()
│   ├── OnPlayerProximity(PlayerCharacter)
│   ├── OnInteraction(PlayerCharacter)
│   └── OnQuestUpdate(QuestID, StepIndex)
│
├── Functions
│   ├── InitializeDialogue(NPCName, DialogueData)
│   ├── StartDialogue(PlayerCharacter)
│   ├── UpdateDialogue(ChoiceIndex)
│   ├── EndDialogue()
│   ├── CheckQuestAvailability()
│   ├── AddReputation(Amount)
│   ├── RemoveReputation(Amount)
│   └── GetReputation() → Float
│
└── Timers
    ├── DialogueTimer
    ├── InteractionCooldownTimer
    └── QuestUpdateTimer
```

#### Key Functions

**InitializeDialogue(NPCName, DialogueData)**
- Input: NPC name, dialogue data asset
- Output: None
- Description: Initialize dialogue component with NPC-specific data
- Steps:
  1. Set NPCName
  2. Set CurrentDialogue
  3. Reset CurrentLineIndex to 0
  4. Reset BranchingChoice to -1
  5. Reset IsDialogueActive to false
  6. Set InteractionCooldown to 0

**StartDialogue(PlayerCharacter)**
- Input: Player character reference
- Output: None
- Description: Start dialogue with player
- Steps:
  1. Check IsDialogueActive → if true, return
  2. Check InteractionCooldown → if > 0, return
  3. Check QuestAvailability → if false, return
  4. Set IsDialogueActive to true
  5. Set InteractionCooldown to 30 seconds
  6. Play Animation(Greeting)
  7. Show Dialogue Widget
  8. Set CurrentLineIndex to 0
  9. Update Dialogue Widget with CurrentLine

**UpdateDialogue(ChoiceIndex)**
- Input: Choice index from player
- Output: None
- Description: Update dialogue based on player choice
- Steps:
  1. Check IsDialogueActive → if false, return
  2. Set BranchingChoice to ChoiceIndex
  3. Get BranchingOptions from CurrentDialogue
  4. Check if ChoiceIndex is valid
  5. If valid:
    - Set CurrentLineIndex to ChoiceIndex
    - Update Dialogue Widget with new line
    - Add Reputation based on choice
    - Check for quest trigger
  6. If invalid:
    - Show error message

**EndDialogue()**
- Input: None
- Output: None
- Description: End current dialogue
- Steps:
  1. Set IsDialogueActive to false
  2. Hide Dialogue Widget
  3. Stop Dialogue Timer
  4. Reset CurrentLineIndex to 0
  5. Reset BranchingChoice to -1

**CheckQuestAvailability()**
- Input: None
- Output: Boolean (is quest available)
- Description: Check if NPC can give quest
- Steps:
  1. Get NPC_QuestActive from Blackboard
  2. Get NPC_Reputation from Blackboard
  3. Get QuestReputationRequired from CurrentDialogue
  4. Check if NPC_QuestActive is false
  5. Check if NPC_Reputation >= QuestReputationRequired
  6. Return result

---

### 2.2 Dialogue Data Structure (`DT_NPC_Dialogue_[NPCName]_v01`)

#### Data Structure
```
DT_NPC_Dialogue_[NPCName]_v01
├── NPCName (String)
├── DialogueLines (Array of String)
├── BranchingOptions (Array of DialogueOption)
├── QuestGiver (Boolean)
├── QuestID (String)
├── QuestReputationRequired (Float)
├── ReputationGain (Float)
├── ReputationLoss (Float)
└── CulturalTone (String)
```

#### DialogueOption Structure
```
DialogueOption
├── OptionText (String)
├── NextLineIndex (Integer)
├── ReputationChange (Float)
├── QuestTrigger (Boolean)
├── QuestStep (Integer)
└── Gesture (Enum: Handshake, Nod, Bow, Wave)
```

#### Example: Auntie Efua
```
NPCName: "AuntieEfua"
DialogueLines: [
  "Good morning! Welcome to my shop.",
  "How can I help you today?",
  "I have fresh fruits and vegetables.",
  "The market is busy today, isn't it?"
]
BranchingOptions: [
  {
    OptionText: "Can I get some tomatoes?",
    NextLineIndex: 1,
    ReputationChange: 0.5,
    QuestTrigger: false,
    Gesture: Handshake
  },
  {
    OptionText: "Do you have any news?",
    NextLineIndex: 2,
    ReputationChange: 0.3,
    QuestTrigger: true,
    QuestStep: 1,
    Gesture: Nod
  }
]
QuestGiver: true
QuestID: "Quest_AuntieEfua_Journal"
QuestReputationRequired: 1.0
ReputationGain: 1.0
ReputationLoss: -0.5
CulturalTone: "Ghanaian, friendly, warm"
```

---

### 2.3 Quest Component Blueprint (`BP_NPC_QuestComponent_v01`)

#### Component Structure
```
BP_NPC_QuestComponent_v01
├── Variables
│   ├── CurrentQuest (QuestData)
│   ├── QuestStep (Integer)
│   ├── QuestActive (Boolean)
│   ├── QuestMarker (Actor)
│   ├── QuestTimer (Float)
│   └── QuestReward (QuestReward)
│
├── Events
│   ├── InitializeComponent()
│   ├── BeginPlay()
│   ├── OnQuestUpdate(QuestID, StepIndex)
│   └── OnQuestComplete(QuestID)
│
├── Functions
│   ├── GiveQuest(QuestID)
│   ├── UpdateQuestStep(StepIndex)
│   ├── CompleteQuest()
│   ├── ShowQuestMarker()
│   ├── HideQuestMarker()
│   ├── CheckQuestProgress()
│   └── GiveQuestReward()
│
└── Timers
    └── QuestTimer
```

#### Key Functions

**GiveQuest(QuestID)**
- Input: Quest ID string
- Output: Boolean (success)
- Description: Give quest to player
- Steps:
  1. Check QuestActive → if true, return false
  2. Get QuestData from QuestManager
  3. Set CurrentQuest to QuestData
  4. Set QuestStep to 0
  5. Set QuestActive to true
  6. Show Quest Marker
  7. Update Quest Widget
  8. Return true

**UpdateQuestStep(StepIndex)**
- Input: Step index integer
- Output: None
- Description: Update quest step
- Steps:
  1. Check QuestActive → if false, return
  2. Set QuestStep to StepIndex
  3. Update Quest Widget
  4. Check if QuestStep == QuestData.TotalSteps
  5. If yes:
    - Call CompleteQuest()
    - Give Quest Reward

**CompleteQuest()**
- Input: None
- Output: None
- Description: Complete current quest
- Steps:
  1. Set QuestActive to false
  2. Hide Quest Marker
  3. Update Quest Widget to complete
  4. Give Quest Reward
  5. Add Reputation based on quest
  6. Reset CurrentQuest

**ShowQuestMarker()**
- Input: None
- Output: None
- Description: Show quest marker above NPC
- Steps:
  1. Create Quest Marker Actor
  2. Set Marker Location to NPC Location
  3. Set Marker Color to Quest Color
  4. Set Marker Text to Quest Name
  5. Set Marker Active to true
  6. Set QuestMarker to Marker

**HideQuestMarker()**
- Input: None
- Output: None
- Description: Hide quest marker
- Steps:
  1. Check if QuestMarker is valid
  2. If yes:
    - Set Marker Active to false
    - Destroy Marker
    - Set QuestMarker to null

---

## 3. VISUAL / RIG / ANIMATION SETUP

### 3.1 NPC Base Blueprint (`BP_NPC_Base_v01`)

#### Component Structure
```
BP_NPC_Base_v01
├── Components
│   ├── CharacterMesh (SkeletalMeshComponent)
│   │   ├── Mesh: [MetaHuman or Custom]
│   │   ├── LOD: LOD0-3
│   │   └── Attachments: Clothing, Props, Accessories
│   ├── DialogueComponent (BP_NPC_DialogueComponent_v01)
│   ├── QuestComponent (BP_NPC_QuestComponent_v01)
│   ├── BehaviorTreeComponent (BehaviorTreeComponent)
│   ├── BlackboardComponent (BlackboardComponent)
│   ├── AIController (AIController)
│   ├── CapsuleComponent (Collision)
│   └── SceneComponent (Root)
│
├── Variables
│   ├── NPCName (String)
│   ├── NPCType (Enum: Resident, Vendor, Student, Official, etc.)
│   ├── District (Enum: Riverside, Kumasi, Cape Coast, etc.)
│   ├── DailySchedule (Struct)
│   ├── IsPersistent (Boolean)
│   ├── SpawnLocation (Vector)
│   └── CurrentState (Enum)
│
├── Events
│   ├── InitializeComponent()
│   ├── BeginPlay()
│   ├── OnSpawned()
│   ├── OnPlayerProximity(PlayerCharacter)
│   ├── OnInteraction(PlayerCharacter)
│   ├── OnDanger(DangerLevel)
│   ├── OnDeath()
│   └── OnQuestComplete(QuestID)
│
├── Functions
│   ├── InitializeNPC(NPCData)
│   ├── SetDailySchedule(ScheduleData)
│   ├── SetDistrict(DistrictType)
│   ├── SetNPCType(NPCType)
│   ├── SetPersistent(Bool)
│   ├── GetNPCName() → String
│   ├── GetNPCType() → Enum
│   ├── GetDistrict() → Enum
│   ├── GetReputation() → Float
│   ├── AddReputation(Amount)
│   ├── RemoveReputation(Amount)
│   ├── CheckInteractable() → Boolean
│   ├── TriggerDialogue(PlayerCharacter)
│   ├── TriggerQuest(PlayerCharacter)
│   └── FleeFromDanger(DangerLevel)
│
└── Timers
    ├── SpawnTimer
    ├── InteractionCooldownTimer
    └── DangerTimer
```

#### Key Events

**OnSpawned()**
- Description: Called when NPC spawns in world
- Steps:
  1. Set SpawnLocation to current location
  2. Initialize Blackboard with default values
  3. Set DailySchedule based on NPCType
  4. Set IsPersistent based on NPCType
  5. Set District based on location
  6. Initialize Behavior Tree
  7. Start InteractionCooldownTimer (30 seconds)
  8. Check DEV_NPC_Debug flag
  9. If debug enabled:
     - Show NPC name above head
     - Show current state
     - Show spawn zone

**OnPlayerProximity(PlayerCharacter)**
- Description: Called when player is nearby
- Steps:
  1. Get distance to player
  2. Check if distance < 500
  3. If yes:
     - Check InteractionCooldownTimer
     - If cooldown > 0, return
     - Check IsInteractable
     - If true:
       - TriggerDialogue(PlayerCharacter)
       - Play Animation(Greeting)

**OnInteraction(PlayerCharacter)**
- Description: Called when player interacts with NPC
- Steps:
  1. Check IsInteractable
  2. If true:
     - Start Dialogue Component
     - Play Animation(Interaction)
     - Update Blackboard State to Interaction

**OnDanger(DangerLevel)**
- Description: Called when danger is detected
- Steps:
  1. Set NPC_DangerLevel to DangerLevel
  2. If DangerLevel > 0.7:
     - Trigger Behavior Tree Danger Handler
     - Play Animation(Flee or Confront)
     - Update Blackboard State to Danger
     - Call for Help if danger level > 0.9

---

### 3.2 Shared Animation Blueprint (`ABP_NPC_Shared_v01`)

#### Anim Sequences

**Idle Animations**
- `Idle_Walk_01` (Standing idle, slight movement)
- `Idle_Walk_02` (Slight head movement)
- `Idle_Observation` (Looking around)
- `Idle_Work` (Working animation for vendors)
- `Idle_Study` (Studying animation for students)

**Walk/Run Animations**
- `Walk_01` (Normal walk)
- `Walk_02` (Carrying items)
- `Run_01` (Running)
- `Run_02` (Running with urgency)

**Gesture Animations**
- `Gesture_Greeting_Handshake` (Handshake)
- `Gesture_Greeting_Nod` (Nod)
- `Gesture_Greeting_Bow` (Bow to elders)
- `Gesture_Greeting_Wave` (Wave)
- `Gesture_Sad_ShakeHead` (Shake head)
- `Gesture_Sad_Sigh` (Sigh)
- `Gesture_Happy_Smile` (Smile)
- `Gesture_Happy_Wave` (Happy wave)
- `Gesture_Angry_Frown` (Frown)
- `Gesture_Angry_Point` (Point)

**Emotion Animations**
- `Emotion_Happy` (Happy expression)
- `Emotion_Sad` (Sad expression)
- `Emotion_Angry` (Angry expression)
- `Emotion_Neutral` (Neutral expression)

**Danger Animations**
- `Danger_Flee` (Running away)
- `Danger_CallForHelp` (Calling for help)
- `Danger_Confront` (Confronting danger)
- `Danger_Fight` (Fighting)

#### Blend Spaces

**BlendSpace_Gait**
- Inputs: WalkSpeed, RunSpeed
- Outputs: Walk animation, Run animation
- Blend: Linear interpolation based on speed

**BlendSpace_Expression**
- Inputs: Happiness, Sadness, Anger, Neutral
- Outputs: Emotion animation
- Blend: Weighted blend based on emotion values

---

### 3.3 LOD Setup

#### LOD Levels
| LOD Level | Mesh Complexity | Animation Complexity | Dialogue Component | Quest Component |
|-----------|------------------|----------------------|-------------------|-----------------|
| LOD0 | 100% | 100% | Enabled | Enabled |
| LOD1 | 50% | 75% | Enabled | Enabled |
| LOD2 | 25% | 50% | Enabled | Enabled |
| LOD3 | 12.5% | 25% | Disabled | Disabled |

#### LOD Settings
- **LOD0**: Full detail, used for close-up (0-500 units)
- **LOD1**: Reduced detail, used for medium distance (500-1000 units)
- **LOD2**: Simplified detail, used for far distance (1000-2000 units)
- **LOD3**: Minimal detail, used for very far distance (2000+ units)

#### Performance Optimization
- Reduce mesh vertex count at LOD2+
- Simplify animations at LOD2+
- Disable dialogue component at LOD3
- Disable quest component at LOD3
- Reduce shadow casting at LOD2+
- Reduce particle effects at LOD2+

---

## 4. SPAWNING & WORLD POPULATION

### 4.1 Spawner Blueprint (`BP_NPC_Spawner_v01`)

#### Component Structure
```
BP_NPC_Spawner_v01
├── Variables
│   ├── SpawnPool (DT_NPC_SpawnPool)
│   ├── CurrentPopulation (Integer)
│   ├── MaxPopulation (Integer)
│   ├── TimeOfDay (Float)
│   ├── SpawnRate (Float)
│   ├── District (Enum)
│   └── IsEnabled (Boolean)
│
├── Events
│   ├── InitializeComponent()
│   ├── BeginPlay()
│   ├── OnTimeOfDayChanged(NewTime)
│   ├── OnZoneLoaded(ZoneName)
│   └── OnZoneUnloaded(ZoneName)
│
├── Functions
│   ├── SpawnNPC(NPCType, Location)
│   ├── DespawnNPC(NPCReference)
│   ├── UpdatePopulation(TimeOfDay)
│   ├── GetSpawnPool(District, TimeOfDay)
│   ├── GetPopulation() → Integer
│   ├── SetMaxPopulation(MaxPop)
│   ├── SetSpawnRate(Rate)
│   └── EnableSpawner(Bool)
│
└── Timers
    ├── SpawnTimer
    └── PopulationCheckTimer
```

#### Key Functions

**SpawnNPC(NPCType, Location)**
- Input: NPC type enum, location vector
- Output: NPC reference
- Description: Spawn an NPC at specified location
- Steps:
  1. Check IsEnabled → if false, return null
  2. Check CurrentPopulation < MaxPopulation
  3. If yes:
    - Get NPC Blueprint based on NPCType
    - Spawn NPC at Location
    - Set NPC District
    - Set NPC DailySchedule
    - Set NPC IsPersistent based on NPCType
    - Initialize NPC
    - Add to CurrentPopulation
    - Return NPC reference
  4. If no:
    - Return null

**DespawnNPC(NPCReference)**
- Input: NPC reference
- Output: Boolean (success)
- Description: Despawn an NPC
- Steps:
  1. Check if NPCReference is valid
  2. If yes:
    - Check if NPC is Persistent
    - If Persistent, return false (cannot despawn)
    - Destroy NPC
    - Subtract from CurrentPopulation
    - Return true
  3. If no:
    - Return false

**UpdatePopulation(TimeOfDay)**
- Input: Time of day (0-24)
- Output: None
- Description: Update population based on time of day
- Steps:
  1. Set TimeOfDay to input
  2. Get SpawnPool for District and TimeOfDay
  3. Calculate target population based on time
  4. If CurrentPopulation < TargetPopulation:
    - Spawn NPCs until CurrentPopulation == TargetPopulation
  5. If CurrentPopulation > TargetPopulation:
    - Despawn NPCs until CurrentPopulation == TargetPopulation

**GetSpawnPool(District, TimeOfDay)**
- Input: District enum, time of day
- Output: SpawnPool data asset
- Description: Get spawn pool for district and time
- Steps:
  1. Get District Name from District enum
  2. Get Time Filter from TimeOfDay
  3. Check if Time is within filter range
  4. If yes:
    - Return SpawnPool asset for District
  5. If no:
    - Return null (no spawning allowed)

---

### 4.2 Spawn Pool Data (`DT_NPC_SpawnPool_[City/Zone]_v01`)

#### Data Structure
```
DT_NPC_SpawnPool_[City/Zone]_v01
├── DistrictName (String)
├── ZoneName (String)
├── NPCTypes (Array of NPCType)
├── SpawnPoints (Array of Vector)
├── MaxPopulation (Integer)
├── SpawnRate (Float)
├── TimeFilters (TimeFilter)
└── PersistentNPCs (Array of String)
```

#### TimeFilter Structure
```
TimeFilter
├── StartHour (Integer)
├── EndHour (Integer)
├── PeakHours (Array of Integer)
└── OffHours (Array of Integer)
```

#### Example: New Accra Market District
```
DistrictName: "NewAccra"
ZoneName: "MarketDistrict"
NPCTypes: [
  "Vendor",
  "Customer",
  "Police",
  "Resident"
]
SpawnPoints: [
  Vector(100, 0, 100),
  Vector(200, 0, 100),
  Vector(100, 0, 200),
  Vector(200, 0, 200)
]
MaxPopulation: 50
SpawnRate: 0.5 (every 2 seconds)
TimeFilters: {
  StartHour: 6,
  EndHour: 18,
  PeakHours: [12, 13, 14, 15],
  OffHours: [19, 20, 21, 22, 23, 0, 1, 2, 3, 4, 5]
}
PersistentNPCs: [
  "AuntieEfua",
  "BabaHassan"
]
```

---

### 4.3 Persistent Key NPCs

#### Auntie Efua (`BP_NPC_AuntieEfua_v01`)
```
NPCName: "AuntieEfua"
NPCType: "Vendor"
District: "NewAccra"
Location: Vector(150, 0, 150)
DailySchedule: {
  StartHour: 6,
  EndHour: 18,
  Activity: "Work",
  WorkLocation: Vector(150, 0, 150)
}
IsPersistent: true
QuestGiver: true
QuestID: "Quest_AuntieEfua_Journal"
```

#### Baba Hassan (`BP_NPC_BabaHassan_v01`)
```
NPCName: "BabaHassan"
NPCType: "Resident"
District: "NewAccra"
Location: Vector(300, 0, 300)
DailySchedule: {
  StartHour: 7,
  EndHour: 9,
  Activity: "Commute",
  HomeLocation: Vector(300, 0, 300),
  WorkLocation: Vector(500, 0, 500)
}
IsPersistent: true
```

#### Kwame (`BP_NPC_Kwame_v01`)
```
NPCName: "Kwame"
NPCType: "Student"
District: "Riverside"
Location: Vector(400, 0, 400)
DailySchedule: {
  StartHour: 8,
  EndHour: 15,
  Activity: "School",
  SchoolLocation: Vector(400, 0, 400)
}
IsPersistent: true
```

---

## 5. INTEGRATION & DEV NOTES

### 5.1 Connection to Player Systems

#### BP_Theo_Player_v01 Integration
```
BP_Theo_Player_v01
├── Events
│   ├── OnSpawned()
│   │   └── Call BP_NPC_Spawner_v01.EnableSpawner(true)
│   ├── OnInteraction(NPCReference)
│   │   └── Call NPCReference.TriggerDialogue(Player)
│   └── OnQuestComplete(QuestID)
│       └── Call NPCReference.OnQuestComplete(QuestID)
└── Variables
    ├── CurrentReputation (Float)
    ├── QuestManager (QuestManagerComponent)
    └── InteractionCooldown (Float)
```

### 5.2 Connection to Chapter 1 Opening Scenes

#### Level_Chapter1_Opening.umap
```
Level_Chapter1_Opening.umap
├── NPCs
│   ├── Riverside Primary
│   │   ├── BP_NPC_Student_v01 (x5)
│   │   └── BP_NPC_Teacher_v01 (x2)
│   ├── Auntie Efua's Shop
│   │   ├── BP_NPC_AuntieEfua_v01
│   │   └── BP_NPC_Vendor_v01 (x2)
│   ├── Kwame's Location
│   │   ├── BP_NPC_Kwame_v01
│   │   └── BP_NPC_Bully_v01 (x2)
│   └── Baba Hassan's Home
│       └── BP_NPC_BabaHassan_v01
├── Spawners
│   ├── BP_NPC_Spawner_v01 (New Accra)
│   ├── BP_NPC_Spawner_v01 (Riverside)
│   └── BP_NPC_Spawner_v01 (Kumasi)
└── Quest Markers
    ├── Quest_AuntieEfua_Journal
    ├── Quest_Kwame_Introduction
    └── Quest_BabaHassan_Home
```

### 5.3 Connection to Existing Input/Interaction Systems

#### Input System Integration
```
Input System
├── Interaction Input (E or Click)
│   └── Raycast to NPC
│       └── Call NPC.OnInteraction(Player)
├── Dialogue Input (E)
│   └── Call DialogueComponent.UpdateDialogue(ChoiceIndex)
└── Quest Input (Tab)
    └── Call QuestComponent.ShowQuestMarker()
```

### 5.4 Debug Flags

#### Config: `Config/DefaultNPC.ini`
```
[/Script/EarthAgain.NPCSystem]
DEV_NPC_Debug=true
DEV_NPC_ShowNames=true
DEV_NPC_ShowStates=true
DEV_NPC_ShowSpawnZones=true
DEV_NPC_ShowQuestMarkers=true
DEV_NPC_ShowReputation=true
```

#### Debug Features
- **Show Names**: Display NPC names above heads
- **Show States**: Display current behavior state
- **Show Spawn Zones**: Display spawn zone indicators
- **Show Quest Markers**: Display quest marker locations
- **Show Reputation**: Display reputation score

---

## 📝 Summary

This blueprint outlines the complete NPC system for Earth Again. Follow the setup order in SETUP_GUIDE.md to implement this system in the main project.

**Key Files**:
- `BT_NPC_Shared_v01.uasset` - Behavior Tree template
- `BP_NPC_DialogueComponent_v01.uasset` - Dialogue system
- `BP_NPC_QuestComponent_v01.uasset` - Quest system
- `BP_NPC_Base_v01.uasset` - NPC base blueprint
- `ABP_NPC_Shared_v01.uasset` - Shared animations
- `BP_NPC_Spawner_v01.uasset` - Spawner system
- `DT_NPC_SpawnPool_[City/Zone]_v01.uasset` - Spawn pool data

**Team Alignment**:
- Georgy (3D assets): Create meshes, props, accessories
- Emmyjay (animations): Create animation sets, blend spaces
- Theo/Hajara (player): Integrate NPC system with player
- Link Games Studio: Review and approve

---

**End of Blueprint Outlines**