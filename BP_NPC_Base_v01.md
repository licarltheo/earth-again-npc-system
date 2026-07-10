# BP_NPC_Base_v01 - NPC Character Blueprint Base

## Purpose
Base blueprint for all NPCs, compatible with shared project skeleton and Emmyjay's retargeting pipeline.

## Properties

### Components
- **CharacterMovementComponent:** Standard UE5 character movement
- **DialogueComponent:** Reference to BP_NPC_DialogueComponent_v01
- **BehaviorComponent:** Reference to BT_NPC_Shared_v01
- **SpawnComponent:** Reference to spawner system

### Variables
```cpp
UPROPERTY(EditAnywhere, Category = "NPC")
TEnumAsByte<ENPCRole> NPCRole;

UPROPERTY(EditAnywhere, Category = "NPC")
TEnumAsByte<ENPCDistrict> NPCDistrict;

UPROPERTY(EditAnywhere, Category = "NPC")
TEnumAsByte<ENPCState> CurrentState;

UPROPERTY(EditAnywhere, Category = "NPC")
FString NPCName;

UPROPERTY(EditAnywhere, Category = "NPC")
TArray<FString> DialogueIDs;

UPROPERTY(EditAnywhere, Category = "NPC")
TArray<FString> QuestIDs;

UPROPERTY(EditAnywhere, Category = "NPC")
bool bIsKeyNPC = false;

UPROPERTY(EditAnywhere, Category = "NPC")
bool bIsPersistent = true;

UPROPERTY(EditAnywhere, Category = "NPC")
FVector HomeLocation;

UPROPERTY(EditAnywhere, Category = "NPC")
FRotator HomeRotation;

UPROPERTY(EditAnywhere, Category = "NPC")
FDateTime LastSpawnTime;
```

## NPC Roles

```cpp
UENUM(BlueprintType)
enum class ENPCRole : uint8
{
    Citizen UMETA(DisplayName = "Citizen"),
    Student UMETA(DisplayName = "Student"),
    Vendor UMETA(DisplayName = "Vendor"),
    Police UMETA(DisplayName = "Police"),
    GangMember UMETA(DisplayName = "Gang Member"),
    Government UMETA(DisplayName = "Government"),
    CircleAgent UMETA(DisplayName = "Circle Agent"),
    FamilyMember UMETA(DisplayName = "Family Member")
};
```

## NPC Districts

```cpp
UENUM(BlueprintType)
enum class ENPCDistrict : uint8
{
    Riverside UMETA(DisplayName = "Riverside"),
    Kumasi UMETA(DisplayName = "Kumasi"),
    CapeCoast UMETA(DisplayName = "Cape Coast"),
    NewAccra UMETA(DisplayName = "New Accra"),
    Tamale UMETA(DisplayName = "Tamale"),
    CircleFoundation UMETA(DisplayName = "Circle Foundation")
};
```

## NPC States

```cpp
UENUM(BlueprintType)
enum class ENPCState : uint8
{
    Idle UMETA(DisplayName = "Idle"),
    Walking UMETA(DisplayName = "Walking"),
    Working UMETA(DisplayName = "Working"),
    Sleeping UMETA(DisplayName = "Sleeping"),
    Dialogue UMETA(DisplayName = "Dialogue"),
    Combat UMETA(DisplayName = "Combat"),
    Fleeing UMETA(DisplayName = "Fleeing"),
    Questing UMETA(DisplayName = "Questing")
};
```

## Functions

### SetNPCRole(ENPCRole NewRole)
- Set the NPC's role
- Update dialogue IDs based on role
- Update appearance based on role

### SetNPCDistrict(ENPCDistrict NewDistrict)
- Set the NPC's district
- Update appearance based on district
- Update dialogue IDs based on district

### SetState(ENPCState NewState)
- Set the NPC's current state
- Update behavior tree
- Update animation state
- Update quest marker visibility

### GetHomeLocation()
- Return the NPC's home location

### SetHomeLocation(FVector Location)
- Set the NPC's home location

### IsAvailableForInteraction()
- Check if NPC is available for interaction
- Not working, sleeping, or in combat

### OnPlayerProximity()
- Called when player is near
- Check for greetings
- Check for dialogue triggers

### OnPlayerFar()
- Called when player is far
- Stop dialogue if active
- Resume routine

## Event Graph

### OnConstruction
1. Update appearance based on Role and District
2. Set default home location
3. Initialize dialogue component
4. Initialize behavior tree

### BeginPlay
1. Set initial state to Idle
2. Set LastSpawnTime to current time
3. Initialize behavior tree
4. Initialize dialogue component
5. Check for key NPC persistence

### Tick
1. Update behavior tree
2. Update dialogue component
3. Update quest marker visibility
4. Update state machine

### OnDamage
1. Set state to Fleeing
2. Call for help
3. Flee from danger

### OnDeath
1. Remove from spawner pool
2. Disable quest markers
3. Disable dialogue

## Appearance Rules

### Riverside District
- Modest clothing
- Bright colors
- Casual styles
- School uniforms for students

### Kumasi District
- Tech-industry attire
- Modern clothing
- Casual but professional

### Cape Coast District
- Heritage styles
- Traditional clothing
- Earth tones

### New Accra District
- Modern fashion
- Business attire
- Trendy styles

### Circle Foundation
- Uniforms
- Professional attire
- Discreet appearance

## LOD Optimization

### LOD Settings
- LOD0: High detail (close range)
- LOD1: Medium detail (medium range)
- LOD2: Low detail (far range)
- LOD3: Very low detail (very far range)

### LOD Distance Settings
- LOD0: 0 - 500 cm
- LOD1: 500 - 1500 cm
- LOD2: 1500 - 3000 cm
- LOD3: 3000+ cm

### Performance Settings
- Disable shadows for LOD3
- Disable reflections for LOD3
- Reduce polygon count for LOD3
- Disable particle effects for LOD3

## Integration with Existing Systems

### Player Character
- Compatible with Theo/Hajara blueprints
- Use same input system
- Use same interaction system

### Locomotion System
- Compatible with main character locomotion
- Use same IK system
- Use same collision system

### Quest System
- Compatible with existing quest system
- Use same quest markers
- Use same quest tracking

### Dialogue System
- Compatible with BP_NPC_DialogueComponent_v01
- Use same dialogue tree structure
- Use same reputation system

## Dependencies
- UE5.2+ Character Blueprint
- UE5.2+ Animation Blueprint (ABP_NPC_Shared_v01)
- UE5.2+ Blackboard System
- UE5.2+ Behavior Tree System
- UE5.2+ Quest System
- UE5.2+ Dialogue System
- Shared Project Skeleton
- Emmyjay's Retargeting Pipeline

## Version
v01

## Author
Earth Again Team

## Last Updated
2026-07-10