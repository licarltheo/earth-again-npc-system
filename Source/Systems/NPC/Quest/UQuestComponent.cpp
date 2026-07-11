#include "UQuestComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	bIsQuestGiver = false;
	ReputationRequired = 0.5f;
	ReputationGain = 0.5f;
	ReputationLoss = -0.5f;
	QuestMarkerType = EQuestMarkerType::Arrow;
	QuestMarkerColor = FLinearColor::Green;
	QuestMarkerText = TEXT("Quest");
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize quest progress
	QuestProgress.Empty();
	QuestSteps.Empty();
	QuestRewards.Empty();
	
	// Initialize active quests
	ActiveQuestIDs.Empty();
	
	// Initialize completed quests
	CompletedQuestIDs.Empty();
	
	// Initialize available quests
	AvailableQuestIDs.Empty();
	
	// Create quest marker if needed
	if (!QuestMarker)
	{
		CreateQuestMarker();
	}
}

void UQuestComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update quest marker visibility
	UpdateQuestMarkerVisibility();
	
	// Process quest progress
	if (CurrentQuestID != TEXT(""))
	{
		// TODO: Process quest progress
		// This will be implemented by quest system
	}
}

void UQuestComponent::InitializeQuests(TArray<FString> QuestIDs)
{
	AvailableQuestIDs = QuestIDs;
	
	// TODO: Load quest data from QuestIDs
	// This will be implemented by quest system
}

void UQuestComponent::GiveQuest(FString QuestID)
{
	// Check if quest is available
	if (!AvailableQuestIDs.Contains(QuestID))
	{
		return;
	}
	
	// Check if player has required reputation
	if (ReputationRequired > 0.0f)
	{
		// TODO: Check player reputation
		// This will be implemented by quest system
		return;
	}
	
	// Add quest to active quests
	ActiveQuestIDs.Add(QuestID);
	
	// Set current quest
	CurrentQuestID = QuestID;
	
	// Initialize quest progress
	QuestProgress.Add(QuestID, 0);
	QuestSteps.Add(QuestID, 0);
	
	// Show quest marker
	ShowQuestMarker();
	
	// TODO: Update quest widget
	// This will be implemented by UI designers
}

void UQuestComponent::UpdateQuestStep(FString QuestID, int32 StepIndex)
{
	// Check if quest is active
	if (!ActiveQuestIDs.Contains(QuestID))
	{
		return;
	}
	
	// Update quest step
	QuestSteps.Add(QuestID, StepIndex);
	
	// Check if quest is complete
	if (StepIndex >= 10) // TODO: Get total steps from quest data
	{
		CompleteQuest(QuestID);
	}
	
	// TODO: Update quest widget
	// This will be implemented by UI designers
}

void UQuestComponent::CompleteQuest(FString QuestID)
{
	// Check if quest is active
	if (!ActiveQuestIDs.Contains(QuestID))
	{
		return;
	}
	
	// Mark quest as complete
	ActiveQuestIDs.Remove(QuestID);
	CompletedQuestIDs.Add(QuestID);
	
	// Hide quest marker
	HideQuestMarker();
	
	// Give quest reward
	GiveQuestReward(QuestID);
	
	// Add reputation based on quest
	AddReputation(ReputationGain);
	
	// TODO: Update quest widget to complete
	// This will be implemented by UI designers
	
	// TODO: Notify player of quest completion
	// This will be implemented by quest system
}

void UQuestComponent::ShowQuestMarker()
{
	// Check if quest marker already exists
	if (QuestMarker)
	{
		QuestMarker->SetActorHiddenInGame(false);
		return;
	}
	
	// Create quest marker
	CreateQuestMarker();
}

void UQuestComponent::HideQuestMarker()
{
	// Hide quest marker
	if (QuestMarker)
	{
		QuestMarker->SetActorHiddenInGame(true);
	}
}

void UQuestComponent::CreateQuestMarker()
{
	// Create quest marker actor
	// TODO: Implement quest marker creation
	// This will be implemented by quest system
}

bool UQuestComponent::CheckQuestProgress(FString QuestID)
{
	// Check quest progress
	if (QuestProgress.Contains(QuestID))
	{
		return QuestProgress[QuestID] > 0;
	}
	
	return false;
}

void UQuestComponent::GiveQuestReward(FString QuestID)
{
	// Give quest reward
	if (QuestRewards.Contains(QuestID))
	{
		FQuestReward Reward = QuestRewards[QuestID];
		
		// TODO: Give reward to player
		// This will be implemented by quest system
	}
	
	// TODO: Add reputation based on quest
	// This will be implemented by quest system
}

TArray<FString> UQuestComponent::GetAvailableQuests()
{
	return AvailableQuestIDs;
}

TArray<FString> UQuestComponent::GetActiveQuests()
{
	return ActiveQuestIDs;
}

TArray<FString> UQuestComponent::GetCompletedQuests()
{
	return CompletedQuestIDs;
}

void UQuestComponent::OnReputationChange(float NewReputation)
{
	// Update quest marker visibility based on reputation
	UpdateQuestMarkerVisibility();
	
	// TODO: Notify quest system of reputation change
	// This will be implemented by quest system
}

void UQuestComponent::UpdateQuestMarkerVisibility()
{
	// Check if quest marker exists
	if (!QuestMarker)
	{
		return;
	}
	
	// Check if NPC is available for interaction
	// Not working, sleeping, or in combat
	bool bIsAvailable = true;
	
	// TODO: Check NPC state
	// This will be implemented by NPC system
	
	// Check if player is in range
	float Distance = FVector::Dist(GetOwner()->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	
	if (Distance > 500.0f)
	{
		bIsAvailable = false;
	}
	
	// Check if quest is available
	if (!bIsQuestGiver)
	{
		bIsAvailable = false;
	}
	
	// Check if player has required reputation
	if (ReputationRequired > 0.0f)
	{
		// TODO: Check player reputation
		// This will be implemented by quest system
		bIsAvailable = false;
	}
	
	// Hide or show quest marker
	QuestMarker->SetActorHiddenInGame(!bIsAvailable);
}