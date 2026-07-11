#include "UDialogueComponent.h"
#include "Kismet/GameplayStatics.h"

UDialogueComponent::UDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	Reputation = 0.5f;
	CurrentState = ENPCDialogueState::Idle;
	NPCName = TEXT("NPC");
	InteractionCooldown = 30.0f;
}

void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize dialogue history
	DialogueHistory.Empty();
	
	// Initialize available quests
	AvailableQuests.Empty();
}

void UDialogueComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update interaction cooldown
	if (InteractionCooldown > 0.0f)
	{
		InteractionCooldown -= DeltaTime;
	}
	
	// Process dialogue if active
	if (CurrentState == ENPCDialogueState::Processing)
	{
		// TODO: Process dialogue nodes
	}
}

void UDialogueComponent::InitializeDialogue(FString NPCName, TArray<FString> DialogueIDs)
{
	this->NPCName = NPCName;
	
	// TODO: Load dialogue tree from DialogueIDs
	// This will be implemented by designers
}

void UDialogueComponent::StartDialogue(AActor* Player)
{
	// Check if dialogue is active
	if (CurrentState == ENPCDialogueState::Active)
	{
		return;
	}
	
	// Check interaction cooldown
	if (InteractionCooldown > 0.0f)
	{
		return;
	}
	
	// Check quest availability
	if (!CheckQuestAvailability(TEXT("")))
	{
		return;
	}
	
	// Set dialogue state to active
	CurrentState = ENPCDialogueState::Active;
	
	// Set interaction cooldown
	InteractionCooldown = 30.0f;
	
	// TODO: Play greeting animation
	// This will be implemented by animators
	
	// TODO: Show dialogue widget
	// This will be implemented by UI designers
	
	// TODO: Set current dialogue ID
	// This will be implemented by designers
}

void UDialogueComponent::ProcessDialogue(FString NodeID)
{
	// Check if dialogue is active
	if (CurrentState != ENPCDialogueState::Active)
	{
		return;
	}
	
	// Set dialogue state to processing
	CurrentState = ENPCDialogueState::Processing;
	
	// Find dialogue node
	FDialogueNode* DialogueNode = nullptr;
	for (FDialogueNode& Node : DialogueTree)
	{
		if (Node.NodeID == NodeID)
		{
			DialogueNode = &Node;
			break;
		}
	}
	
	if (!DialogueNode)
	{
		// Invalid node ID
		CurrentState = ENPCDialogueState::Idle;
		return;
	}
	
	// Update dialogue history
	DialogueHistory.Add(NodeID);
	
	// Update reputation based on choice
	Reputation += DialogueNode->ReputationChange;
	
	// Clamp reputation between 0.0 and 1.0
	Reputation = FMath::Clamp(Reputation, 0.0f, 1.0f);
	
	// Check for quest triggers
	if (DialogueNode->bIsQuestStart)
	{
		// TODO: Start quest
		// This will be implemented by quest system
	}
	
	if (DialogueNode->bIsQuestUpdate)
	{
		// TODO: Update quest
		// This will be implemented by quest system
	}
	
	if (DialogueNode->bIsQuestComplete)
	{
		// TODO: Complete quest
		// This will be implemented by quest system
	}
	
	// Select next node
	if (DialogueNode->NextNodes.Num() > 0)
	{
		// TODO: Show next dialogue node
		// This will be implemented by UI designers
	}
	else
	{
		// No more nodes, end dialogue
		EndDialogue();
	}
}

void UDialogueComponent::EndDialogue()
{
	// Set dialogue state to idle
	CurrentState = ENPCDialogueState::Idle;
	
	// TODO: Hide dialogue widget
	// This will be implemented by UI designers
	
	// TODO: Play idle animation
	// This will be implemented by animators
}

void UDialogueComponent::UpdateReputation(float Delta)
{
	Reputation += Delta;
	
	// Clamp reputation between 0.0 and 1.0
	Reputation = FMath::Clamp(Reputation, 0.0f, 1.0f);
	
	// TODO: Notify quest system of reputation change
	// This will be implemented by quest system
}

bool UDialogueComponent::CheckQuestAvailability(FString QuestID)
{
	// Check if quest is available
	if (bIsQuestGiver)
	{
		// TODO: Check if player has required reputation
		// This will be implemented by quest system
		return true;
	}
	
	return false;
}

TArray<FString> UDialogueComponent::GetAvailableQuests()
{
	return AvailableQuests;
}

float UDialogueComponent::GetReputation()
{
	return Reputation;
}

TEnumAsByte<ENPCDialogueState> UDialogueComponent::GetCurrentState()
{
	return CurrentState;
}