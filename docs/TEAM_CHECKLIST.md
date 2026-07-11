# Earth Again - NPC System Team Checklist

**Internal Dev-Ready | Link Games Studio | Unreal Engine 5.2+**

---

## 📋 Overview
This checklist provides alignment tasks for Georgy (3D assets) and Emmyjay (animations) to ensure their work integrates seamlessly with the NPC system.

---

## 🎬 Checklist for Georgy (3D Assets)

### Character Meshes
- [ ] Create NPC character meshes (MetaHuman or custom)
- [ ] Create district-specific clothing variations
- [ ] Create props (market items, bags, tools)
- [ ] Create accessories (jewelry, hats, bags)
- [ ] Provide weight painting guides for joint deformation
- [ ] Create LOD meshes for performance
- [ ] Create facial variation assets (skin tones, features)
- [ ] Create animation reference meshes

### Riverside District
- [ ] Modest clothing meshes
- [ ] Bright color variations
- [ ] Casual styles
- [ ] School uniforms for students
- [ ] Props: School bags, books, notebooks

### Kumasi District
- [ ] Tech-industry attire meshes
- [ ] Modern clothing variations
- [ ] Casual but professional styles
- [ ] Props: Laptops, tablets, phones

### Cape Coast District
- [ ] Heritage style meshes
- [ ] Traditional clothing variations
- [ ] Earth tone color palette
- [ ] Props: Traditional items, crafts

### New Accra District
- [ ] Modern fashion meshes
- [ ] Business attire variations
- [ ] Trendy styles
- [ ] Props: Briefcases, phones, accessories

### Circle Foundation
- [ ] Uniform meshes
- [ ] Professional attire variations
- [ ] Discreet appearance
- [ ] Props: ID cards, equipment

### LOD Meshes
- [ ] LOD0: High detail (100% complexity)
- [ ] LOD1: Medium detail (50% complexity)
- [ ] LOD2: Low detail (25% complexity)
- [ ] LOD3: Very low detail (12.5% complexity)

### Weight Painting Guides
- [ ] Joint deformation guides for all meshes
- [ ] Clothing weight painting guides
- [ ] Prop attachment guides
- [ ] Accessory attachment guides

### Facial Variations
- [ ] Skin tone variations (10+ tones)
- [ ] Facial feature variations
- [ ] Age variations (child, adult, elder)
- [ ] Gender variations

### Props and Accessories
- [ ] Market items (stalls, baskets, produce)
- [ ] Bags (school bags, shopping bags, tool bags)
- [ ] Tools (hammers, wrenches, etc.)
- [ ] Accessories (jewelry, hats, bags)
- [ ] District-specific props

### Integration Checklist
- [ ] Ensure meshes are compatible with shared skeleton
- [ ] Ensure meshes are compatible with MetaHuman
- [ ] Ensure meshes are compatible with Emmyjay's retargeting pipeline
- [ ] Ensure meshes are compatible with BP_NPC_Base_v01
- [ ] Ensure meshes are compatible with ABP_NPC_Shared_v01
- [ ] Ensure meshes are compatible with UE5.2+ physics system
- [ ] Ensure meshes are compatible with UE5.2+ collision system

---

## 🎬 Checklist for Emmyjay (Animations)

### Shared Animation Sets
- [ ] Create shared animation sets (idle, walk, run, gesture)
- [ ] Create emotion-based animations (happy, sad, angry, neutral)
- [ ] Create district-specific animations (cultural gestures)
- [ ] Create dialogue animations (head nods, hand gestures)
- [ ] Create danger animations (flee, fight, call for help)
- [ ] Create quest interaction animations (giving items, receiving)
- [ ] Create retargeting guide for shared skeleton
- [ ] Create blend space definitions (gait, expression)

### Idle Animations
- [ ] `Idle_Walk_01` (Standing idle, slight movement)
- [ ] `Idle_Walk_02` (Slight head movement)
- [ ] `Idle_Observation` (Looking around)
- [ ] `Idle_Work` (Working animation for vendors)
- [ ] `Idle_Study` (Studying animation for students)
- [ ] `Idle_Relax` (Relaxing animation)
- [ ] `Idle_Eat` (Eating animation)

### Walk/Run Animations
- [ ] `Walk_01` (Normal walk)
- [ ] `Walk_02` (Carrying items)
- [ ] `Run_01` (Running)
- [ ] `Run_02` (Running with urgency)
- [ ] `Walk_Carrying` (Carrying heavy items)
- [ ] `Run_Carrying` (Running with heavy items)

### Gesture Animations
- [ ] `Gesture_Greeting_Handshake` (Handshake)
- [ ] `Gesture_Greeting_Nod` (Nod)
- [ ] `Gesture_Greeting_Bow` (Bow to elders)
- [ ] `Gesture_Greeting_Wave` (Wave)
- [ ] `Gesture_Sad_ShakeHead` (Shake head)
- [ ] `Gesture_Sad_Sigh` (Sigh)
- [ ] `Gesture_Happy_Smile` (Smile)
- [ ] `Gesture_Happy_Wave` (Happy wave)
- [ ] `Gesture_Angry_Frown` (Frown)
- [ ] `Gesture_Angry_Point` (Point)
- [ ] `Gesture_Agree_Nod` (Agreement nod)
- [ ] `Gesture_Disagree_ShakeHead` (Disagreement shake head)

### Emotion Animations
- [ ] `Emotion_Happy` (Happy expression)
- [ ] `Emotion_Sad` (Sad expression)
- [ ] `Emotion_Angry` (Angry expression)
- [ ] `Emotion_Neutral` (Neutral expression)
- [ ] `Emotion_Surprised` (Surprised expression)
- [ ] `Emotion_Fearful` (Fearful expression)

### Danger Animations
- [ ] `Danger_Flee` (Running away)
- [ ] `Danger_CallForHelp` (Calling for help)
- [ ] `Danger_Confront` (Confronting danger)
- [ ] `Danger_Fight` (Fighting)
- [ ] `Danger_Defend` (Defending self)

### Work Animations
- [ ] `Work_Vendor` (Vendor work)
- [ ] `Work_Official` (Government work)
- [ ] `Work_Student` (Student work)
- [ ] `Work_Farmer` (Farmer work)
- [ ] `Work_Craftsman` (Craftsman work)

### School Animations
- [ ] `School_Attend` (Attending class)
- [ ] `School_Study` (Studying)
- [ ] `School_Socialize` (Socializing with peers)
- [ ] `School_Lunch` (Eating lunch)
- [ ] `School_Recess` (Playing during recess)

### Cultural Animations
- [ ] `Cultural_Greeting_Handshake` (Ghanaian handshake)
- [ ] `Cultural_Greeting_Nod` (Ghanaian nod)
- [ ] `Cultural_Greeting_Bow` (Bow to elders)
- [ ] `Cultural_Gesture_Point` (Ghanaian pointing)
- [ ] `Cultural_Gesture_Wave` (Ghanaian wave)

### Blend Spaces
- [ ] `BlendSpace_Gait` (Walk/Run speed)
- [ ] `BlendSpace_Expression` (Emotion blend)
- [ ] `BlendSpace_Speed` (Speed blend)
- [ ] `BlendSpace_Gesture` (Gesture blend)

### Retargeting Guide
- [ ] Create retargeting guide for shared skeleton
- [ ] Ensure bone mapping is correct
- [ ] Ensure bone hierarchy is correct
- [ ] Ensure bone weights are correct
- [ ] Ensure animation curves are correct

### Blend Space Definitions
- [ ] `BlendSpace_Gait` inputs: WalkSpeed, RunSpeed
- [ ] `BlendSpace_Expression` inputs: Happiness, Sadness, Anger, Neutral
- [ ] `BlendSpeed_Speed` inputs: Speed, Direction
- [ ] `BlendSpace_Gesture` inputs: GestureType, Intensity

### LOD Animations
- [ ] LOD0: Full animation complexity
- [ ] LOD1: Reduced animation complexity (75%)
- [ ] LOD2: Simplified animations (50%)
- [ ] LOD3: Minimal animations (25%)

### Integration Checklist
- [ ] Ensure animations are compatible with shared skeleton
- [ ] Ensure animations are compatible with MetaHuman
- [ ] Ensure animations are compatible with Emmyjay's retargeting pipeline
- [ ] Ensure animations are compatible with BP_NPC_Base_v01
- [ ] Ensure animations are compatible with ABP_NPC_Shared_v01
- [ ] Ensure animations are compatible with UE5.2+ animation system
- [ ] Ensure animations are compatible with UE5.2+ blend space system
- [ ] Ensure animations are compatible with UE5.2+ animation slots

---

## 📦 File Naming Convention

### 3D Assets (Georgy)
```
[District]_[Role]_[Variation]_[LOD].uasset
```

Examples:
- `Riverside_Student_Casual_LOD0.uasset`
- `Kumasi_Vendor_Tech_LOD1.uasset`
- `CapeCoast_Elder_Heritage_LOD2.uasset`
- `NewAccra_Official_Business_LOD3.uasset`

### Animations (Emmyjay)
```
[AnimationType]_[Variation]_[LOD].uasset
```

Examples:
- `Idle_Walk_01_LOD0.uasset`
- `Walk_02_Carrying_LOD1.uasset`
- `Gesture_Greeting_Handshake_LOD2.uasset`
- `Emotion_Happy_LOD3.uasset`

### Blend Spaces
```
BlendSpace_[Type]_[LOD].uasset
```

Examples:
- `BlendSpace_Gait_LOD0.uasset`
- `BlendSpace_Expression_LOD1.uasset`
- `BlendSpace_Speed_LOD2.uasset`

---

## 🎯 Alignment Tasks

### Georgy
1. Review BP_NPC_Base_v01.md for mesh requirements
2. Review ABP_NPC_Shared_v01.md for animation compatibility
3. Review BT_NPC_Shared_v01.md for behavior requirements
4. Review DT_NPC_SpawnPool_NewAccra_v01.md for spawn requirements
5. Create meshes with correct LOD levels
6. Create weight painting guides
7. Create props and accessories
8. Test meshes in UE5.2+ with BP_NPC_Base_v01
9. Test meshes with ABP_NPC_Shared_v01
10. Test meshes with BT_NPC_Shared_v01

### Emmyjay
1. Review BP_NPC_Base_v01.md for animation requirements
2. Review ABP_NPC_Shared_v01.md for animation sets
3. Review BT_NPC_Shared_v01.md for behavior animations
4. Review BP_NPC_DialogueComponent_v01.md for dialogue animations
5. Review BP_NPC_QuestComponent_v01.md for quest animations
6. Create animation sets with correct LOD levels
7. Create blend space definitions
8. Create retargeting guide
9. Test animations in UE5.2+ with ABP_NPC_Shared_v01
10. Test animations with BP_NPC_Base_v01
11. Test animations with BT_NPC_Shared_v01

---

## ⚠️ Important Notes

1. **All** assets must be compatible with the shared skeleton
2. **All** assets must be compatible with MetaHuman
3. **All** assets must be compatible with Emmyjay's retargeting pipeline
4. **All** assets must be compatible with UE5.2+ systems
5. **All** assets must follow the file naming convention
6. **All** assets must be optimized for performance
7. **All** assets must be tested in UE5.2+
8. **All** assets must be reviewed by the Earth Again team
9. **All** assets must be approved before merging
10. **All** assets must be documented

---

## 📞 Support

For questions or issues, contact the Earth Again development team.

---

**End of Team Checklist**