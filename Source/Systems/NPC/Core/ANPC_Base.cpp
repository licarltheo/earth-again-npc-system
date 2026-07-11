#include "ANPC_Base.h"
#include "DialogueComponent.h"
#include "QuestComponent.h"
#include "BehaviorTreeComponent.h"
#include "BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ANPC_Base::ANPC_Base()
{
	// Set default values
	PrimaryActorTick.bCanEverTick = true;
	
	// Enable tick for behavior updates
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	// Set default NPC properties
	NPCRole = ENPCRole::Citizen;
	NPCDistrict = ENPCDistrict::NewAccra;
	CurrentState = ENPCState::Idle;
	NPCName = TEXT("NPC");
	bIsKeyNPC = false;
	bIsPersistent = true;
	Reputation = 0.5f;
	InteractionCooldown = 30.0f;
	bIsInteractable = true;
	bIsInDanger = false;
	
	// Set default home location
	HomeLocation = GetActorLocation();
	HomeRotation = GetActorRotation();
	LastSpawnTime = FDateTime::Now();
	
	// Create components
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	
	// Set initial state to Idle
	SetState(ENPCState::Idle);
	
	// Set LastSpawnTime to current time
	LastSpawnTime = FDateTime::Now();
	
	// Initialize behavior tree
	if (BehaviorTreeComponent)
	{
		// TODO: Initialize behavior tree
		// BehaviorTreeComponent->StartTree(BehaviorTree);
	}
	
	// Initialize dialogue component
	if (DialogueComponent)
	{
		DialogueComponent->InitializeDialogue(NPCName, DialogueIDs);
	}
	
	// Initialize quest component
	if (QuestComponent)
	{
		QuestComponent->InitializeQuests(QuestIDs);
	}
	
	// Check for key NPC persistence
	if (bIsKeyNPC)
	{
		// TODO: Register as persistent NPC
	}
}

void ANPC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update behavior tree
	if (BehaviorTreeComponent)
	{
		// TODO: Update behavior tree
	}
	
	// Update dialogue component
	if (DialogueComponent)
	{
		DialogueComponent->Tick(DeltaTime);
	}
	
	// Update quest component
	if (QuestComponent)
	{
		QuestComponent->Tick(DeltaTime);
	}
	
	// Update state machine
	UpdateStateMachine(DeltaTime);
	
	// Update interaction cooldown
	if (InteractionCooldown > 0.0f)
	{
		InteractionCooldown -= DeltaTime;
	}
	
	// Update danger timer
	if (bIsInDanger)
	{
		// TODO: Handle danger
	}
}

void ANPC_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	// Update appearance based on Role and District
	UpdateAppearance();
	
	// Set default home location
	if (HomeLocation == FVector::ZeroVector)
	{
		HomeLocation = GetActorLocation();
	}
	
	if (HomeRotation == FRotator::ZeroRotator)
	{
		HomeRotation = GetActorRotation();
	}
	
	// Initialize dialogue component
	if (DialogueComponent)
	{
		DialogueComponent->InitializeDialogue(NPCName, DialogueIDs);
	}
	
	// Initialize behavior tree
	if (BehaviorTreeComponent)
	{
		// TODO: Initialize behavior tree
	}
}

void ANPC_Base::Destroyed()
{
	Super::Destroyed();
	
	// Remove from spawner pool
	if (bIsPersistent)
	{
		// TODO: Unregister as persistent NPC
	}
	
	// Disable quest markers
	if (QuestComponent)
	{
		QuestComponent->HideQuestMarker();
	}
	
	// Disable dialogue
	if (DialogueComponent)
	{
		DialogueComponent->EndDialogue();
	}
}

void ANPC_Base::SetNPCRole(ENPCRole NewRole)
{
	NPCRole = NewRole;
	
	// Update dialogue IDs based on role
	UpdateDialogueIDs();
	
	// Update appearance based on role
	UpdateAppearance();
}

void ANPC_Base::SetNPCDistrict(ENPCDistrict NewDistrict)
{
	NPCDistrict = NewDistrict;
	
	// Update appearance based on district
	UpdateAppearance();
	
	// Update dialogue IDs based on district
	UpdateDialogueIDs();
}

void ANPC_Base::SetState(ENPCState NewState)
{
	CurrentState = NewState;
	
	// Update behavior tree
	if (BehaviorTreeComponent)
	{
		// TODO: Update behavior tree state
	}
	
	// Update animation state
	UpdateAnimationState();
	
	// Update quest marker visibility
	if (QuestComponent)
	{
		QuestComponent->UpdateQuestMarkerVisibility();
	}
}

FVector ANPC_Base::GetHomeLocation()
{
	return HomeLocation;
}

void ANPC_Base::SetHomeLocation(FVector Location)
{
	HomeLocation = Location;
}

bool ANPC_Base::IsAvailableForInteraction()
{
	// Check if NPC is available for interaction
	// Not working, sleeping, or in combat
	if (CurrentState == ENPCState::Working ||
		CurrentState == ENPCState::Sleeping ||
		CurrentState == ENPCState::Combat ||
		CurrentState == ENPCState::Fleeing)
	{
		return false;
	}
	
	// Check interaction cooldown
	if (InteractionCooldown > 0.0f)
	{
		return false;
	}
	
	// Check if interactable
	if (!bIsInteractable)
	{
		return false;
	}
	
	return true;
}

void ANPC_Base::OnPlayerProximity(ACharacter* Player)
{
	// Check if player is nearby
	float Distance = FVector::Dist(GetActorLocation(), Player->GetActorLocation());
	
	if (Distance < 500.0f)
	{
		// Check interaction cooldown
		if (InteractionCooldown > 0.0f)
		{
			return;
		}
		
		// Check if interactable
		if (!IsAvailableForInteraction())
		{
			return;
		}
		
		// Trigger dialogue
		if (DialogueComponent)
		{
			DialogueComponent->StartDialogue(Player);
		}
		
		// Play greeting animation
		PlayGreetingAnimation();
	}
}

void ANPC_Base::OnPlayerFar()
{
	// Stop dialogue if active
	if (DialogueComponent)
	{
		DialogueComponent->EndDialogue();
	}
	
	// Resume routine
	SetState(ENPCState::Idle);
}

void ANPC_Base::OnDamage(float DamageAmount, AActor* DamageCauser)
{
	// Set state to Fleeing
	SetState(ENPCState::Fleeing);
	
	// Call for help
	CallForHelp();
	
	// Flee from danger
	FleeFromDanger(DamageCauser);
}

void ANPC_Base::OnDeath()
{
	// Remove from spawner pool
	if (bIsPersistent)
	{
		// TODO: Unregister as persistent NPC
	}
	
	// Disable quest markers
	if (QuestComponent)
	{
		QuestComponent->HideQuestMarker();
	}
	
	// Disable dialogue
	if (DialogueComponent)
	{
		DialogueComponent->EndDialogue();
	}
}

void ANPC_Base::OnQuestComplete(FString QuestID)
{
	// Add reputation based on quest
	AddReputation(0.5f);
	
	// Notify quest component
	if (QuestComponent)
	{
		QuestComponent->OnQuestComplete(QuestID);
	}
}

float ANPC_Base::GetReputation()
{
	return Reputation;
}

void ANPC_Base::AddReputation(float Amount)
{
	Reputation += Amount;
	
	// Clamp between 0.0 and 1.0
	Reputation = FMath::Clamp(Reputation, 0.0f, 1.0f);
	
	// Notify quest component of reputation change
	if (QuestComponent)
	{
		QuestComponent->OnReputationChange(Reputation);
	}
}

void ANPC_Base::RemoveReputation(float Amount)
{
	Reputation -= Amount;
	
	// Clamp between 0.0 and 1.0
	Reputation = FMath::Clamp(Reputation, 0.0f, 1.0f);
	
	// Notify quest component of reputation change
	if (QuestComponent)
	{
		QuestComponent->OnReputationChange(Reputation);
	}
}

TEnumAsByte<ENPCState> ANPC_Base::GetCurrentState()
{
	return CurrentState;
}

TEnumAsByte<ENPCRole> ANPC_Base::GetNPCRole()
{
	return NPCRole;
}

TEnumAsByte<ENPCDistrict> ANPC_Base::GetNPCDistrict()
{
	return NPCDistrict;
}

FString ANPC_Base::GetNPCName()
{
	return NPCName;
}

void ANPC_Base::UpdateAppearance()
{
	// TODO: Update appearance based on Role and District
	// This will be implemented by 3D artists
}

void ANPC_Base::UpdateDialogueIDs()
{
	// TODO: Update dialogue IDs based on Role and District
	// This will be implemented by designers
}

void ANPC_Base::UpdateAnimationState()
{
	// TODO: Update animation state based on CurrentState
	// This will be implemented by animators
}

void ANPC_Base::PlayGreetingAnimation()
{
	// TODO: Play greeting animation
	// This will be implemented by animators
}

void ANPC_Base::CallForHelp()
{
	// TODO: Call for help
	// This will be implemented by behavior tree
}

void ANPC_Base::FleeFromDanger(AActor* Aggressor)
{
	// TODO: Flee from danger
	// This will be implemented by behavior tree
}

void ANPC_Base::UpdateStateMachine(float DeltaTime)
{
	// TODO: Update state machine
	// This will be implemented by behavior tree
}