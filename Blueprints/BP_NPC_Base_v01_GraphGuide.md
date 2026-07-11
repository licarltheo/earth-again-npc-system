# Blueprint Graph Implementation - BP_NPC_Base_v01
===================================================

## How to Create BP_NPC_Base_v01 in Unreal Engine 5.2+

### Step 1: Create the Blueprint Class
1. Right-click in Content Browser
2. Search for "ANPC_Base"
3. Select "BP_NPC_Base_v01"
4. Click "Create"

### Step 2: Add Components
1. Click "Components" tab
2. Click "+ Add" button
3. Add these components:
   - **CharacterMesh** (SkeletalMeshComponent) - Set to your NPC mesh
   - **DialogueComponent** (UDialogueComponent)
   - **QuestComponent** (UQuestComponent)
   - **BehaviorTreeComponent** (UBehaviorTreeComponent)
   - **BlackboardComponent** (UBlackboardComponent)
   - **AIController** (AIController)
   - **CapsuleComponent** (Collision) - Rename to "CapsuleCollision"
   - **SceneComponent** (SceneComponent) - Rename to "RootScene"

### Step 3: Configure Variables
1. Click "Variables" tab
2. Add these variables:

#### NPC Properties
- **NPCName** (String) - Default: "NPC"
- **NPCRole** (Enum: Citizen, Student, Vendor, Police, GangMember, Government, CircleAgent, FamilyMember)
- **NPCDistrict** (Enum: Riverside, Kumasi, CapeCoast, NewAccra, Tamale, CircleFoundation)
- **CurrentState** (Enum: Idle, Walking, Working, Sleeping, Dialogue, Combat, Fleeing, Questing)
- **IsKeyNPC** (Boolean) - Default: false
- **IsPersistent** (Boolean) - Default: true
- **HomeLocation** (Vector) - Default: (0, 0, 0)
- **HomeRotation** (Rotator) - Default: (0, 0, 0)
- **Reputation** (Float) - Default: 0.5
- **InteractionCooldown** (Float) - Default: 30.0

#### Component References
- **DialogueComponent** (ObjectProperty) - Reference to DialogueComponent
- **QuestComponent** (ObjectProperty) - Reference to QuestComponent
- **BehaviorTreeComponent** (ObjectProperty) - Reference to BehaviorTreeComponent
- **BlackboardComponent** (ObjectProperty) - Reference to BlackboardComponent

### Step 4: Event Graph Implementation

#### BeginPlay Event
```
BeginPlay
├── Set CurrentState to Idle
├── Set LastSpawnTime to Now
├── Initialize DialogueComponent
│   ├── Set NPCName to NPCName variable
│   └── Set DialogueIDs to DialogueIDs array
├── Initialize QuestComponent
│   ├── Set QuestIDs to QuestIDs array
│   └── Set IsQuestGiver to IsQuestGiver boolean
├── Initialize BehaviorTreeComponent
│   └── Start Behavior Tree
└── Set HomeLocation to ActorLocation
```

#### Tick Event
```
Tick (DeltaSeconds)
├── Update BehaviorTreeComponent
├── Update DialogueComponent
│   └── Tick DialogueComponent
├── Update QuestComponent
│   └── Tick QuestComponent
├── Update State Machine
│   └── UpdateStateMachine(DeltaSeconds)
└── Update InteractionCooldown
    └── Subtract DeltaSeconds from InteractionCooldown
```

#### OnConstruction Event
```
OnConstruction(Transform)
├── Update Appearance based on Role and District
├── Set HomeLocation to ActorLocation
├── Set HomeRotation to ActorRotation
├── Initialize DialogueComponent
└── Initialize BehaviorTreeComponent
```

#### Destroyed Event
```
Destroyed
├── Remove from Spawner Pool (if Persistent)
├── Hide Quest Marker (if QuestComponent exists)
└── End Dialogue (if DialogueComponent exists)
```

### Step 5: Function Implementations

#### SetNPCRole(ENPCRole)
```
SetNPCRole(NewRole)
├── Set NPCRole variable to NewRole
├── Update DialogueIDs based on Role
├── Update Appearance based on Role
└── Return
```

#### SetNPCDistrict(ENPCDistrict)
```
SetNPCDistrict(NewDistrict)
├── Set NPCDistrict variable to NewDistrict
├── Update Appearance based on District
└── Update DialogueIDs based on District
```

#### SetState(ENPCState)
```
SetState(NewState)
├── Set CurrentState variable to NewState
├── Update BehaviorTreeComponent state
├── Update Animation State
├── Update Quest Marker Visibility
│   └── Call QuestComponent.UpdateQuestMarkerVisibility()
└── Return
```

#### GetHomeLocation() -> Vector
```
GetHomeLocation()
├── Return HomeLocation variable
└── Return
```

#### SetHomeLocation(Vector)
```
SetHomeLocation(Location)
├── Set HomeLocation variable to Location
└── Return
```

#### IsAvailableForInteraction() -> Boolean
```
IsAvailableForInteraction()
├── Check CurrentState
│   ├── If Working or Sleeping or Combat or Fleeing
│   │   └── Return false
│   └── If Idle or Walking or Dialogue or Questing
│       └── Continue
├── Check InteractionCooldown
│   ├── If > 0.0
│   │   └── Return false
│   └── If <= 0.0
│       └── Continue
├── Check bIsInteractable
│   ├── If false
│   │   └── Return false
│   └── If true
│       └── Return true
└── Return true
```

#### OnPlayerProximity(ACharacter*)
```
OnPlayerProximity(Player)
├── Calculate Distance to Player
│   └── GetActorLocation() - Player.GetActorLocation()
├── If Distance < 500.0
│   ├── Check InteractionCooldown
│   │   ├── If > 0.0
│   │   │   └── Return
│   │   └── If <= 0.0
│   │       └── Continue
│   ├── Check IsAvailableForInteraction()
│   │   ├── If false
│   │   │   └── Return
│   │   └── If true
│   │       └── Continue
│   ├── Start Dialogue
│   │   └── Call DialogueComponent.StartDialogue(Player)
│   ├── Play Greeting Animation
│   │   └── Call PlayGreetingAnimation()
│   └── Set InteractionCooldown to 30.0
└── Return
```

#### OnPlayerFar()
```
OnPlayerFar()
├── End Dialogue
│   └── Call DialogueComponent.EndDialogue()
└── Set State to Idle
```
`