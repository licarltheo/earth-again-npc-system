# ABP_NPC_Shared_v01 - Shared NPC Animation Blueprint

## Purpose
Shared animation blueprint for all NPCs, compatible with MetaHuman and custom character meshes.

## Properties

### Animation Settings
```cpp
UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> IdleMontages;

UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> WalkMontages;

UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> RunMontages;

UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> GestureMontages;

UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> EmotionMontages;

UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> DangerMontages;

UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> WorkMontages;

UPROPERTY(EditAnywhere, Category = "Animation")
TArray<UAnimMontage*> SchoolMontages;
```

### Blend Spaces
```cpp
UPROPERTY(EditAnywhere, Category = "Animation")
UBlendSpace* BlendSpace_Gait;

UPROPERTY(EditAnywhere, Category = "Animation")
UBlendSpace* BlendSpace_Expression;

UPROPERTY(EditAnywhere, Category = "Animation")
UBlendSpace* BlendSpace_Speed;
```

### Animation Slots
```cpp
UPROPERTY(EditAnywhere, Category = "Animation")
FName SlotName_Gesture;

UPROPERTY(EditAnywhere, Category = "Animation")
FName SlotName_Emotion;

UPROPERTY(EditAnywhere, Category = "Animation")
FName SlotName_Danger;
```

## Anim Sequences

### Idle Animations
- `Idle_Walk_01` (Standing idle, slight movement)
- `Idle_Walk_02` (Slight head movement)
- `Idle_Observation` (Looking around)
- `Idle_Work` (Working animation for vendors)
- `Idle_Study` (Studying animation for students)

### Walk/Run Animations
- `Walk_01` (Normal walk)
- `Walk_02` (Carrying items)
- `Run_01` (Running)
- `Run_02` (Running with urgency)

### Gesture Animations
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

### Emotion Animations
- `Emotion_Happy` (Happy expression)
- `Emotion_Sad` (Sad expression)
- `Emotion_Angry` (Angry expression)
- `Emotion_Neutral` (Neutral expression)

### Danger Animations
- `Danger_Flee` (Running away)
- `Danger_CallForHelp` (Calling for help)
- `Danger_Confront` (Confronting danger)
- `Danger_Fight` (Fighting)

### Work Animations
- `Work_Vendor` (Vendor work)
- `Work_Official` (Government work)
- `Work_Student` (Student work)

### School Animations
- `School_Attend` (Attending class)
- `School_Study` (Studying)
- `School_Socialize` (Socializing with peers)

## Blend Spaces

### BlendSpace_Gait
- **Inputs:** WalkSpeed, RunSpeed
- **Outputs:** Walk animation, Run animation
- **Blend:** Linear interpolation based on speed
- **Purpose:** Smooth gait transitions

### BlendSpace_Expression
- **Inputs:** Happiness, Sadness, Anger, Neutral
- **Outputs:** Emotion animation
- **Blend:** Weighted blend based on emotion values
- **Purpose:** Smooth emotion transitions

### BlendSpace_Speed
- **Inputs:** Speed, Direction
- **Outputs:** Animation based on speed and direction
- **Blend:** Linear interpolation based on speed
- **Purpose:** Smooth speed transitions

## Animation Slots

### Gesture Slot
- Used for greeting animations
- Handshake, Nod, Bow, Wave
- Plays on upper body

### Emotion Slot
- Used for emotion animations
- Happy, Sad, Angry, Neutral
- Plays on face and body

### Danger Slot
- Used for danger animations
- Flee, Fight, Confront
- Plays on full body

## Functions

### PlayIdleAnimation()
- Select random idle animation
- Play animation on CharacterMesh
- Update animation state

### PlayWalkAnimation()
- Select walk animation based on speed
- Play animation on CharacterMesh
- Update animation state

### PlayRunAnimation()
- Select run animation based on urgency
- Play animation on CharacterMesh
- Update animation state

### PlayGestureAnimation(FString GestureName)
- Select gesture animation
- Play animation on GestureSlot
- Update animation state

### PlayEmotionAnimation(FString EmotionName)
- Select emotion animation
- Play animation on EmotionSlot
- Update animation state

### PlayDangerAnimation(FString DangerName)
- Select danger animation
- Play animation on DangerSlot
- Update animation state

### PlayWorkAnimation(FString WorkType)
- Select work animation
- Play animation on CharacterMesh
- Update animation state

### PlaySchoolAnimation(FString SchoolType)
- Select school animation
- Play animation on CharacterMesh
- Update animation state

### UpdateBlendSpaceGait(float WalkSpeed, float RunSpeed)
- Update blend space inputs
- Update animation based on speed

### UpdateBlendSpaceExpression(float Happiness, float Sadness, float Anger)
- Update blend space inputs
- Update animation based on emotion

## Event Graph

### OnSpawned
1. Initialize animation slots
2. Set default animations
3. Load animation assets

### OnStateChange(ENPCState NewState)
1. Select animation based on state
2. Play animation
3. Update animation state

### OnDialogueStart
1. Play greeting animation
2. Play gesture animation

### OnDialogueEnd
1. Play idle animation
2. Clear animation slots

### OnQuestStart
1. Play quest animation
2. Play gesture animation

### OnQuestComplete
1. Play happy animation
2. Play gesture animation

### OnDangerDetected
1. Play danger animation
2. Play flee animation

## Retargeting Guide

### Shared Skeleton
- Use shared project skeleton
- Ensure consistent bone names
- Ensure consistent bone hierarchy
- Ensure consistent bone weights

### Emmyjay's Pipeline
- Follow Emmyjay's retargeting pipeline
- Use Emmyjay's animation sets
- Use Emmyjay's blend spaces
- Use Emmyjay's animation slots

### MetaHuman Support
- Ensure MetaHuman compatibility
- Ensure MetaHuman bone mapping
- Ensure MetaHuman animation support
- Ensure MetaHuman blend space support

## LOD Optimization

### LOD0 (High Detail)
- Full animation complexity
- Full blend space complexity
- Full animation slots

### LOD1 (Medium Detail)
- Reduced animation complexity
- Reduced blend space complexity
- Full animation slots

### LOD2 (Low Detail)
- Simplified animations
- Simplified blend spaces
- Reduced animation slots

### LOD3 (Very Low Detail)
- Minimal animations
- Minimal blend spaces
- Disabled animation slots

## Performance Settings

### Animation Complexity
- LOD0: 100%
- LOD1: 75%
- LOD2: 50%
- LOD3: 25%

### Blend Space Complexity
- LOD0: 100%
- LOD1: 75%
- LOD2: 50%
- LOD3: 25%

### Animation Slots
- LOD0: All slots enabled
- LOD1: All slots enabled
- LOD2: Reduced slots
- LOD3: Disabled

## Notes
- Animation sets must be compatible with shared skeleton
- Animation sets must be compatible with MetaHuman
- Animation sets must be compatible with Emmyjay's pipeline
- Blend spaces must be configured correctly
- Animation slots must be configured correctly
- LOD settings must be optimized for performance

## Dependencies
- UE5.2+ Animation Blueprint
- UE5.2+ Animation System
- UE5.2+ Blend Space System
- UE5.2+ Animation Slots
- Shared Project Skeleton
- MetaHuman Support
- Emmyjay's Animation Sets

## Version
v01

## Author
Earth Again Team

## Last Updated
2026-07-10