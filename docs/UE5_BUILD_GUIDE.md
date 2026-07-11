# Unreal Engine 5.2+ Build Guide - Earth Again NPC System
========================================================

## Prerequisites
- Unreal Engine 5.2 or higher
- Visual Studio 2022 (for C++ development)
- Windows 10/11 (64-bit)
- Git (for cloning the repository)

## Step 1: Clone the Repository
```bash
# Clone the repository
git clone https://github.com/licarltheo/earth-again-npc-system.git

git clone https://github.com/licarltheo/earth-again-npc-system.git EarthAgain

cd EarthAgain
```

## Step 2: Create the Project
1. Open Unreal Engine 5.2+
2. Click "New Project"
3. Select "Empty Project" (C++)
4. Name it "EarthAgain"
5. Select location
6. Click "Create Project"

## Step 3: Copy C++ Files to Project
```bash
# Copy C++ files to your project
# Source/Systems/NPC/Core/ANPC_Base.h
# Source/Systems/NPC/Core/ANPC_Base.cpp
# Source/Systems/NPC/Dialogue/UDialogueComponent.h
# Source/Systems/NPC/Dialogue/UDialogueComponent.cpp
# Source/Systems/NPC/Quest/UQuestComponent.h
# Source/Systems/NPC/Quest/UQuestComponent.cpp
# Source/Systems/NPC/Dialogue/UDialogueWidget.h
# Source/Systems/NPC/Dialogue/UDialogueWidget.cpp
# Source/Systems/NPC/Quest/UQuestWidget.h
# Source/Systems/NPC/Quest/UQuestWidget.cpp
# Source/Systems/NPC/Behavior/UBT_NPC_Shared_v01.h
# Source/Systems/NPC/Animation/UABP_NPC_Shared_v01.h
# Source/Systems/NPC/Spawning/UDT_NPC_SpawnPool.h
```

Copy these files to:
```
EarthAgain/Source/Systems/NPC/Core/ANPC_Base.h
EarthAgain/Source/Systems/NPC/Core/ANPC_Base.cpp
EarthAgain/Source/Systems/NPC/Dialogue/UDialogueComponent.h
EarthAgain/Source/Systems/NPC/Dialogue/UDialogueComponent.cpp
EarthAgain/Source/Systems/NPC/Quest/UQuestComponent.h
EarthAgain/Source/Systems/NPC/Quest/UQuestComponent.cpp
EarthAgain/Source/Systems/NPC/Dialogue/UDialogueWidget.h
EarthAgain/Source/Systems/NPC/Dialogue/UDialogueWidget.cpp
EarthAgain/Source/Systems/NPC/Quest/UQuestWidget.h
EarthAgain/Source/Systems/NPC/Quest/UQuestWidget.cpp
EarthAgain/Source/Systems/NPC/Behavior/UBT_NPC_Shared_v01.h
EarthAgain/Source/Systems/NPC/Animation/UABP_NPC_Shared_v01.h
EarthAgain/Source/Systems/NPC/Spawning/UDT_NPC_SpawnPool.h
```

## Step 4: Create Build Configuration
1. Open `EarthAgain.Build.cs`
2. Add these namespaces:
```csharp
using UnrealBuildTool;
using System.Collections.Generic;

public class EarthAgain : ModuleRules
{
    public EarthAgain(ReadOnlyTargetRules Target) : base(Target)
    {
        // ... existing code ...
        
        // Add NPC System namespaces
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "GameplayAbilities",
            "GameplayTasks",
            "AIModule",
            "GameplayTags",
            "NavigationSystem",
            "GameFramework",
            "PhysicsCore",
            "AnimationCore",
            "BehaviorTree",
            "BlackboardCore",
            "UMG",
            "Slate",
            "SlateCore"
        });
    }
}
```

## Step 5: Build the Project
### Option 1: Build from Unreal Engine
1. Open Unreal Engine 5.2+
2. Open your EarthAgain project
3. Click **Build** button (or press Ctrl+B)
4. Wait for build to complete
5. Click **Compile** button (or press Ctrl+Shift+B)

### Option 2: Build from Command Line
```bash
# Navigate to your project
cd EarthAgain

# Build for development