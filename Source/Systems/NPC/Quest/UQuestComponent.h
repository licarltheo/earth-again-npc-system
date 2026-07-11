#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"

/**
 * Quest Marker Type Enum
 */
uenum(BlueprintType)
class EQuestMarkerType : uint8
{
	Arrow = 0,
	Circle = 1,
	Diamond = 2,
	Star = 3
};

/**
 * NPC Quest Component
 * Handles quest giving, updates, and completion
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EARTHTHAGAIN_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UQuestComponent();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// Quest Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FString> AvailableQuestIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FString> ActiveQuestIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TArray<FString> CompletedQuestIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsQuestGiver = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	float ReputationRequired = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	float ReputationGain = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	float ReputationLoss = -0.5f;
	
	// Quest Marker
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	AActor* QuestMarker = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TEnumAsByte<EQuestMarkerType> QuestMarkerType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FLinearColor QuestMarkerColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FString QuestMarkerText;
	
	// Functions
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void InitializeQuests(TArray<FString> QuestIDs);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuest(FString QuestID);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateQuestStep(FString QuestID, int32 StepIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void CompleteQuest(FString QuestID);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void ShowQuestMarker();
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void HideQuestMarker();
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool CheckQuestProgress(FString QuestID);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveQuestReward(FString QuestID);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<FString> GetAvailableQuests();
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<FString> GetActiveQuests();
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	TArray<FString> GetCompletedQuests();
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void OnReputationChange(float NewReputation);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateQuestMarkerVisibility();
	
protected:
	// Quest Data
	TMap<FString, int32> QuestProgress;
	TMap<FString, int32> QuestSteps;
	
	// Timer
	FTimerHandle QuestTimerHandle;
	
	// Current quest
	FString CurrentQuestID;
	
	// Quest reward
	struct FQuestReward
	{
		FString RewardType;
		int32 RewardAmount;
	};
	TMap<FString, FQuestReward> QuestRewards;
};