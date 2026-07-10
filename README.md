# Earth Again - NPC System

Complete integrated NPC system for Link Games Studio's open-world life simulation RPG.

## Project Info
- **Engine**: Unreal Engine 5.2+
- **Target**: PS5/Xbox Series X/PC
- **Developer**: Link Games Studio
- **Status**: Internal Dev-Ready

## Repository Contents

### 1. NPC BEHAVIOR & AI
- Behavior Trees and Blackboard templates
- Daily life routine logic
- Context-aware reactions
- Priority tiers system

### 2. NPC DIALOGUE & QUEST INTERACTION
- Reusable dialogue system
- Branching conversations
- Quest integration
- Reputation system

### 3. VISUAL / RIG / ANIMATION SETUP
- UE5 Character Blueprint base
- MetaHuman/custom mesh support
- LOD optimization

### 4. SPAWNING & WORLD POPULATION
- District-specific spawn pools
- Time-of-day filtering
- Persistent key NPCs
- World Partition + HLOD integration

### 5. INTEGRATION & DEV NOTES
- Setup order for team
- Debug flags
- Connection to existing systems

## File Structure
```
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

## Quick Start
1. Review the blueprint outlines in the `docs/` folder
2. Follow the setup order in `SETUP_GUIDE.md`
3. Align with Georgy (3D assets) and Emmyjay (animations)

## License
MIT License - Internal Use Only

## Contact
For questions or issues, contact the Earth Again development team.