#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTreeComponent.h"
#include "Blackboard/BlackboardComponent.h"
#include "Blackboard/BlackboardData.h"
#include "BT_NPC_Shared_v01.generated.h"

/**
 * Behavior Tree for NPCs
 * Shared behavior tree template for all NPC types
 */
UCLASS()
class EARTHTHAGAIN_API UBT_NPC_Shared_v01 : public UBehaviorTree
{
	GENERATED_BODY()
	
public:
	UBT_NPC_Shared_v01();
	
	// Blackboard Keys
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_State;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_Role;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_District;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_Player_Distance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_Player_InRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_Player_InDanger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_HomeLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_WorkLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_SchoolLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_CurrentTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_IsWorkingTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_IsSchoolTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_IsHomeTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_HasActiveQuest;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_ActiveQuestID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_Reputation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_IsInCombat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FString Key_NPC_Aggressor;
	
	// Behavior Tree Structure
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTreeAsset* BehaviorTreeAsset;
	
	// Subtrees
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTreeAsset* Subtree_DangerHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTreeAsset* Subtree_InteractionHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTreeAsset* Subtree_RoutineHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	UBehaviorTreeAsset* Subtree_IdleHandler;
	
	// Task Classes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_PlayIdleAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_PlayWalkAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_PlayWorkAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_PlaySchoolAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_StartDialogue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_StartQuest;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_FleeFromDanger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_CallForHelp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_ConfrontAggressor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_GoToLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_CheckProximityToPlayer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTTaskNode> Task_UpdateBlackboardValues;
	
	// Selector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTSelector> Selector_Priority;
	
	// Sequence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTSequence> Sequence_DangerHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTSequence> Sequence_InteractionHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTSequence> Sequence_RoutineHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BehaviorTree")
	TSubclassOf<UBTSequence> Sequence_IdleHandler;
};