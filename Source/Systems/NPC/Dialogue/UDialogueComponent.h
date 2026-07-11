#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"

/**
 * Dialogue Node Structure
 */
USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString NodeID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString Text;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TEnumAsByte<ENPCDialogueType> DialogueType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> NextNodes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsBranch = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsQuestStart = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsQuestUpdate = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsQuestComplete = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float ReputationChange = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString Gesture;
};

/**
 * NPC Dialogue Type Enum
 */
uenum(BlueprintType)
class ENPCDialogueType : uint8
{
	Casual = 0,
	Quest = 1,
	QuestUpdate = 2,
	QuestComplete = 3,
	Greeting = 4,
	Goodbye = 5
};

/**
 * NPC Dialogue Component
 * Handles dialogue interactions, quest integration, and reputation
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EARTHTHAGAIN_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UDialogueComponent();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// Dialogue Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueNode> DialogueTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> DialogueHistory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float Reputation = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TEnumAsByte<ENPCDialogueState> CurrentState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString CurrentDialogueID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsQuestGiver = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> QuestIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> AvailableQuests;
	
	// Functions
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void InitializeDialogue(FString NPCName, TArray<FString> DialogueIDs);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue(AActor* Player);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ProcessDialogue(FString NodeID);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void EndDialogue();
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void UpdateReputation(float Delta);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool CheckQuestAvailability(FString QuestID);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	TArray<FString> GetAvailableQuests();
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	float GetReputation();
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	TEnumAsByte<ENPCDialogueState> GetCurrentState();
	
protected:
	// Dialogue State Enum
	enum class ENPCDialogueState : uint8
	{
		Idle = 0,
		Active = 1,
		Processing = 2,
		Complete = 3
	};
	
	// NPC Name
	FString NPCName;
	
	// Timer
	FTimerHandle DialogueTimerHandle;
	
	// Interaction cooldown
	float InteractionCooldown = 30.0f;
};