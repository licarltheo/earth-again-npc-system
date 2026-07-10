# DT_NPC_SpawnPool_NewAccra_v01 - NPC Spawner System

## Purpose
Spawner system and population logic for New Accra district with district-specific pools, time-of-day filtering, and persistent key NPCs.

## Properties

### Spawner Settings
```cpp
UPROPERTY(EditAnywhere, Category = "Spawner")
TEnumAsByte<ENPCDistrict> TargetDistrict;

UPROPERTY(EditAnywhere, Category = "Spawner")
TEnumAsByte<ENPCRole> RolePool;

UPROPERTY(EditAnywhere, Category = "Spawner")
int32 MaxPopulation = 100;

UPROPERTY(EditAnywhere, Category = "Spawner")
float SpawnInterval = 60.0f;

UPROPERTY(EditAnywhere, Category = "Spawner")
bool bEnableTimeFiltering = true;

UPROPERTY(EditAnywhere, Category = "Spawner")
bool bEnablePersistentNPCs = true;
```

### Time Filter Settings
```cpp
UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime MorningStart = FDateTime(2026, 7, 10, 06, 0, 0);

UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime MorningEnd = FDateTime(2026, 7, 10, 12, 0, 0);

UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime AfternoonStart = FDateTime(2026, 7, 10, 12, 0, 0);

UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime AfternoonEnd = FDateTime(2026, 7, 10, 16, 0, 0);

UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime EveningStart = FDateTime(2026, 7, 10, 16, 0, 0);

UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime EveningEnd = FDateTime(2026, 7, 10, 22, 0, 0);

UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime NightStart = FDateTime(2026, 7, 10, 22, 0, 0);

UPROPERTY(EditAnywhere, Category = "Spawner")
FDateTime NightEnd = FDateTime(2026, 7, 10, 06, 0, 0);
```

### Persistent NPCs
```cpp
UPROPERTY(EditAnywhere, Category = "Spawner")
TArray<FString> KeyNPCNames;

UPROPERTY(EditAnywhere, Category = "Spawner")
TMap<FString, FVector> KeyNPCLocations;

UPROPERTY(EditAnywhere, Category = "Spawner")
TMap<FString, FRotator> KeyNPCRotations;
```

## District-Specific Pools

### Riverside District
- **RolePool:** Student
- **Locations:** Near Riverside Primary School
- **MaxPopulation:** 50
- **SpawnInterval:** 120.0f

### Kumasi District
- **RolePool:** Citizen, Vendor
- **Locations:** Near Kumasi Market
- **MaxPopulation:** 80
- **SpawnInterval:** 90.0f

### Cape Coast District
- **RolePool:** Citizen
- **Locations:** Near Cape Coast Heritage Site
- **MaxPopulation:** 40
- **SpawnInterval:** 180.0f

### New Accra District
- **RolePool:** Citizen, Vendor, Government, CircleAgent
- **Locations:** Financial district, Market zones
- **MaxPopulation:** 100
- **SpawnInterval:** 60.0f

### Tamale District
- **RolePool:** Citizen
- **Locations:** Tamale outskirts
- **MaxPopulation:** 30
- **SpawnInterval:** 240.0f

## Time-of-Day Filtering

### Morning (06:00 - 12:00)
- **Riverside:** Students attending school (spawn rate: high)
- **Kumasi:** Vendors opening stalls (spawn rate: medium)
- **New Accra:** Business people (spawn rate: high)
- **Cape Coast:** Tourists and locals (spawn rate: low)
- **Tamale:** People starting day (spawn rate: low)

### Afternoon (12:00 - 16:00)
- **Riverside:** School in session (spawn rate: high)
- **Kumasi:** Vendors active (spawn rate: high)
- **New Accra:** Peak crowds (spawn rate: very high)
- **Cape Coast:** Sightseeing (spawn rate: medium)
- **Tamale:** Mid-day activities (spawn rate: medium)

### Evening (16:00 - 22:00)
- **Riverside:** School ends (spawn rate: medium)
- **Kumasi:** Vendors closing (spawn rate: medium)
- **New Accra:** Business people leaving (spawn rate: high)
- **Cape Coast:** Evening activities (spawn rate: low)
- **Tamale:** Evening activities (spawn rate: medium)

### Night (22:00 - 06:00)
- **All Districts:** Vendors vanish (spawn rate: 0)
- **New Accra:** Few people out (spawn rate: very low)
- **Riverside:** Students sleeping (spawn rate: 0)
- **Kumasi:** Market closes (spawn rate: 0)
- **Cape Coast:** Quiet (spawn rate: 0)
- **Tamale:** Few people (spawn rate: very low)

## Persistent Key NPCs

### Auntie Efua
- **Role:** Vendor
- **Location:** New Accra Market
- **Rotation:** Facing market entrance
- **Always Spawn:** Yes
- **Work Hours:** 06:00 - 18:00

### Baba Hassan
- **Role:** Government Official
- **Location:** New Accra Government Building
- **Rotation:** Facing building entrance
- **Always Spawn:** Yes
- **Work Hours:** 08:00 - 17:00

### Kwame the Bully
- **Role:** Gang Member
- **Location:** Riverside District
- **Rotation:** Facing school
- **Always Spawn:** Yes
- **Work Hours:** 08:00 - 15:00 (school hours)

## UE5 World Partition + HLOD

### World Partition Settings
- **Partition Size:** 5000 x 5000 cm
- **Partition Grid:** 10 x 10
- **Streaming Distance:** 5000 cm
- **Load Distance:** 10000 cm
- **Unload Distance:** 15000 cm

### HLOD Settings
- **HLOD0:** High detail (0 - 500 cm)
- **HLOD1:** Medium detail (500 - 1500 cm)
- **HLOD2:** Low detail (1500 - 3000 cm)
- **HLOD3:** Very low detail (3000+ cm)

### Spawn Limits per Zone
- **Riverside:** 50 NPCs
- **Kumasi:** 80 NPCs
- **New Accra:** 100 NPCs
- **Cape Coast:** 40 NPCs
- **Tamale:** 30 NPCs

## Performance Settings

### Target FPS
- **Console:** 30 FPS
- **PC:** 60 FPS

### Optimization Settings
- **Shadows:** Disabled for LOD3
- **Reflections:** Disabled for LOD3
- **Particles:** Disabled for LOD3
- **Lighting:** Static lighting for LOD3
- **LOD:** Automatic LOD switching

## Functions

### SpawnNPC()
- Check if population limit reached
- Check if time filter allows spawning
- Check if persistent NPC needs spawning
- Select NPC type from pool
- Spawn NPC at random location
- Set NPC state to Idle
- Update population count

### DespawnNPC(ANPCCharacter* NPC)
- Remove NPC from world
- Update population count
- Check if persistent NPC
- If persistent, respawn at correct time

### UpdatePopulation()
- Check current population
- Adjust spawn rate based on time of day
- Adjust spawn rate based on district density
- Check for persistent NPCs

### GetSpawnRate()
- Return spawn rate based on time of day
- Return spawn rate based on district
- Return spawn rate based on population

### IsTimeForSpawning()
- Check if current time is within spawn window
- Check if time filter is enabled
- Return true/false

### IsPersistentNPC(FString NPCName)
- Check if NPC is a key NPC
- Return true/false

## Event Graph

### OnTick
1. Update current time
2. Update population count
3. Check spawn rate
4. Spawn NPCs if needed
5. Despawn NPCs if needed
6. Update persistent NPCs

### OnWorldPartitionLoaded
1. Initialize spawner
2. Set up spawn zones
3. Load persistent NPCs
4. Set up HLOD

### OnWorldPartitionUnloaded
1. Despawn all NPCs
2. Clear persistent NPCs
3. Reset population count

### OnTimeChange
1. Update time filter
2. Update spawn rate
3. Update persistent NPCs
4. Despawn NPCs if needed

## Notes
- Spawner must be placed in each World Partition
- Persistent NPCs must be registered in KeyNPCNames
- Time filter must be updated for each district
- Spawn limits must be set per zone
- HLOD must be configured correctly
- Performance must be monitored

## Dependencies
- UE5.2+ World Partition
- UE5.2+ HLOD
- UE5.2+ NPC System
- BP_NPC_Base_v01
- BP_NPC_DialogueComponent_v01
- BT_NPC_Shared_v01

## Version
v01

## Author
Earth Again Team

## Last Updated
2026-07-10