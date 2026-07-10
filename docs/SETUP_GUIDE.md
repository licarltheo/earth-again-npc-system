# Earth Again - NPC System Setup Guide

**Internal Dev-Ready | Link Games Studio | Unreal Engine 5.2+**

---

## 📋 Overview
This guide provides the **setup order** for the Earth Again NPC System. Follow this sequence to merge the system into the main project without breaking existing work.

---

## 🎯 Setup Order

### Phase 1: Core Foundation (Day 1-2)

#### 1.1 Create Directory Structure
```bash
# In EarthAgain project
EarthAgain/
├── Source/
│   └── Systems/
│       └── NPC/
│           ├── BehaviorTrees/
│           ├── Dialogue/
│           ├── Spawning/
│           └── Core/
└── Content/
    └── Characters/
        └── NPCs/
            ├── BP_NPC_Base_v01.uasset
            ├── ABP_NPC_Shared_v01.uasset
            └── [NPC-specific assets]
```

#### 1.2 Create Project Config
- **File**: `Config/DefaultNPC.ini`
- **Purpose**: Central configuration for NPC system
- **Key Settings**:
  - Debug flags (`DEV_NPC_Debug`)
  - Spawn limits per zone
  - Time-of-day filtering thresholds
  - Reputation system defaults

#### 1.3 Create Blackboard Keys
- **File**: `Data/Blackboards/BK_NPC_Shared_v01.uasset`
- **Keys to create**:
  - `NPC_State` (Enum: Idle, Routine, Interaction, Danger, Combat)
  - `NPC_DailySchedule` (Struct: Time, Activity, Location)
  - `NPC_InteractionCooldown` (Float)
  - `NPC_Reputation` (Float)
  - `NPC_IsInteractable` (Boolean)
  - `NPC_QuestActive` (Boolean)
  - `NPC_QuestStep` (Integer)

---

### Phase 2: Behavior AI (Day 2-4)

#### 2.1 Create Behavior Tree Template
- **File**: `BT_NPC_Shared_v01.uasset`
- **Structure**:
  - **Root** → Selector
    - **Sequence** → Danger Handler
    - **Sequence** → Interaction Handler
    - **Sequence** → Routine Handler
    - **Sequence** → Idle Handler

- **Subtrees**:
  - `BT_DangerHandler_v01` (Flee, Call for Help, Confront)
  - `BT_InteractionHandler_v01` (Dialogue, Quest, Greeting)
  - `BT_RoutineHandler_v01` (Daily schedule, Pathfinding)
  - `BT_IdleHandler_v01` (Random idle, Observation)

#### 2.2 Create EQS Queries
- **File**: `EQS_NPC_Shared_v01.uasset`
- **Queries**:
  - `EQS_FindSafeSpot` (For danger response)
  - `EQS_FindInteractionSpot` (For dialogue)
  - `EQS_FindPathToLocation` (For routine movement)
  - `EQS_CheckProximityToPlayer` (For greeting/interaction)

#### 2.3 Create Smart Object Sets
- **File**: `SO_NPC_Shared_v01.uasset`
- **Smart Objects**:
  - Market stalls (for vendors)
  - School benches (for students)
  - Home locations (for residents)
  - Government buildings (for officials)

---

### Phase 3: Dialogue System (Day 3-5)

#### 3.1 Create Dialogue Component Blueprint
- **File**: `BP_NPC_DialogueComponent_v01.uasset`
- **Key Functions**:
  - `InitializeDialogue(NPCName, DialogueData)`
  - `StartDialogue(PlayerCharacter)`
  - `UpdateDialogue(ChoiceIndex)`
  - `EndDialogue()`
  - `CheckQuestAvailability()`

#### 3.2 Create Dialogue Data Structure
- **File**: `DT_NPC_Dialogue_[NPCName]_v01.uasset`
- **Data per NPC**:
  - `DialogueLines` (Array of strings)
  - `BranchingOptions` (Array of choices)
  - `QuestGiver` (Boolean)
  - `QuestID` (String)
  - `ReputationRequired` (Float)

#### 3.3 Create Quest Integration
- **File**: `BP_NPC_QuestComponent_v01.uasset`
- **Functions**:
  - `GiveQuest(QuestID)`
  - `UpdateQuestStep(StepIndex)`
  - `CompleteQuest()`
  - `ShowQuestMarker()`
  - `HideQuestMarker()`

---

### Phase 4: Visual Setup (Day 4-6)

#### 4.1 Create NPC Base Blueprint
- **File**: `BP_NPC_Base_v01.uasset`
- **Components**:
  - `CharacterMesh` (MetaHuman or custom)
  - `DialogueComponent` (BP_NPC_DialogueComponent_v01)
  - `QuestComponent` (BP_NPC_QuestComponent_v01)
  - `BehaviorTreeComponent` (BT_NPC_Shared_v01)
  - `BlackboardComponent` (BK_NPC_Shared_v01)

- **Events**:
  - `OnSpawned()` (Initialize state, schedule)
  - `OnPlayerProximity()` (Check greeting)
  - `OnInteraction()` (Start dialogue)
  - `OnDanger()` (Trigger danger handler)

#### 4.2 Create Shared Animation Blueprint
- **File**: `ABP_NPC_Shared_v01.uasset`
- **Anim Sequences**:
  - `Idle_Walk` (Variations: Idle_Walk_1, Idle_Walk_2)
  - `Walk_Run` (Variations: Walk_Run_1, Walk_Run_2)
  - `Gesture_Greeting` (Handshake, Nod, Bow)
  - `Gesture_Sad` (Shake head, Sigh)
  - `Gesture_Happy` (Smile, Wave)
  - `Gesture_Angry` (Frown, Point)

- **Blend Spaces**:
  - `BlendSpace_Gait` (Walk/Run speed)
  - `BlendSpace_Expression` (Emotion blend)

#### 4.3 LOD Setup
- **LOD Levels**: LOD0 (100%), LOD1 (50%), LOD2 (25%), LOD3 (12.5%)
- **LOD Settings**:
  - Reduce mesh complexity at distance
  - Simplify animations at LOD2+
  - Disable dialogue component at LOD3

---

### Phase 5: Spawning System (Day 5-7)

#### 5.1 Create Spawner Blueprint
- **File**: `BP_NPC_Spawner_v01.uasset`
- **Functions**:
  - `SpawnNPC(NPCType, Location)`
  - `DespawnNPC(NPCReference)`
  - `UpdatePopulation(TimeOfDay)`
  - `GetSpawnPool(District, TimeOfDay)`

#### 5.2 Create Spawn Pool Data
- **File**: `DT_NPC_SpawnPool_[City/Zone]_v01.uasset`
- **Data per District**:
  - `NPCTypes` (Array of NPC types)
  - `SpawnPoints` (Array of locations)
  - `MaxPopulation` (Integer)
  - `SpawnRate` (Float)
  - `TimeFilters` (StartHour, EndHour)

#### 5.3 Create Persistent Key NPCs
- **File**: `BP_NPC_AuntieEfua_v01.uasset`
- **BP_NPC_BabaHassan_v01.uasset`
- **BP_NPC_Kwame_v01.uasset`
- **Settings**:
  - Always spawn at assigned location
  - Never replaced by generic NPCs
  - Fixed schedule (no time filtering)

---

### Phase 6: Integration & Testing (Day 6-7)

#### 6.1 Connect to Player Systems
- **File**: `BP_Theo_Player_v01.uasset`
- **Integration Points**:
  - `OnPlayerSpawn()` → Initialize NPC system
  - `OnInteraction()` → Trigger NPC dialogue
  - `OnQuestComplete()` → Update NPC reputation

#### 6.2 Connect to Chapter 1 Scenes
- **File**: `Level_Chapter1_Opening.umap`
- **NPC Placement**:
  - Riverside Primary (Students)
  - Auntie Efua's Shop (Market vendor)
  - Kwame's Location (Bully)
  - Baba Hassan's Home (Resident)

#### 6.3 Debug Flags
- **Config**: `DEV_NPC_Debug = true`
- **Debug Features**:
  - Show NPC names above heads
  - Display behavior state
  - Show spawn zones
  - Display quest markers

---

## 📦 File Naming Convention

All files must follow this pattern:

```
BP_NPC_[Role/Name]_v[Version].uasset
BT_NPC_[BehaviorType]_v[Version].uasset
DT_NPC_[DataType]_[Specific]_v[Version].uasset
ABP_NPC_[AnimationType]_v[Version].uasset
BK_NPC_[BlackboardType]_v[Version].uasset
EQS_NPC_[QueryType]_v[Version].uasset
SO_NPC_[SmartObjectType]_v[Version].uasset
```

**Versioning**: v01, v02, v03 (increment when breaking changes occur)

---

## 🎬 Checklist for Georgy (3D Assets)

- [ ] Create NPC character meshes (MetaHuman or custom)
- [ ] Create district-specific clothing variations
- [ ] Create props (market items, bags, tools)
- [ ] Create accessories (jewelry, hats, bags)
- [ ] Provide weight painting guides for joint deformation
- [ ] Create LOD meshes for performance
- [ ] Create facial variation assets (skin tones, features)
- [ ] Create animation reference meshes

---

## 🎬 Checklist for Emmyjay (Animations)

- [ ] Create shared animation sets (idle, walk, run, gesture)
- [ ] Create emotion-based animations (happy, sad, angry, neutral)
- [ ] Create district-specific animations (cultural gestures)
- [ ] Create dialogue animations (head nods, hand gestures)
- [ ] Create danger animations (flee, fight, call for help)
- [ ] Create quest interaction animations (giving items, receiving)
- [ ] Create retargeting guide for shared skeleton
- [ ] Create blend space definitions (gait, expression)

---

## ⚠️ Important Notes

1. **Do NOT** create conflicting folders or duplicate systems
2. **All** assets must reference existing Earth Again paths
3. **Do NOT** write or reveal restricted story content
4. **Keep** NPC behavior generic enough to support future story additions
5. **Test** with World Partition + HLOD enabled
6. **Verify** performance on PS5/Xbox Series X/PC target hardware

---

## 📞 Support

For questions or issues, contact the Earth Again development team.

---

**End of Setup Guide**