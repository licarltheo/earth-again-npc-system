#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_Base.generated.h"

/**
 * NPC Role Enum
 */
uenum(BlueprintType)
class ENPCRole : uint8
{
	MorningStart = 0,
	MorningEnd = 1,
	AfternoonStart = 2,
	AfternoonEnd = 3,
	EveningStart = 4,
	EveningEnd = 5,
	NightStart = 6,
	NightEnd = 7
};

/**
 * NPC District Enum
 */
uenum(BlueprintType)
class ENPCDistrict : uint8
{
	Riverside = 0,
	Kumasi = 1,
	CapeCoast = 2,
	NewAccra = 3,
	Tamale = 4,
	CircleFoundation = 5
};

/**
 * NPC State Enum
 */
uenum(BlueprintType)
class ENPCState : uint8
{
	Idle = 0,
	Walking = 1,
	Working = 2,
	Sleeping = 3,
	Dialogue = 4,
	Combat = 5,
	Fleeing = 6,
	Questing = 7
};

/**
 * Base NPC Character Class
 * Compatible with shared project skeleton and Emmyjay's retargeting pipeline
 */
UCLASS()
class EARTHTHAGAIN_API ANPC_Base : public ACharacter
{
	GENERATED_BODY()
	
public:
	ANPC_Base();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;
	
	// NPC Properties
	UPROPERTY(EditAnywhere, Category = "NPC")
	TEnumAsByte<ENPCRole> NPCRole;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	TEnumAsByte<ENPCDistrict> NPCDistrict;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	TEnumAsByte<ENPCState> CurrentState;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	FString NPCName;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	TArray<FString> DialogueIDs;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	TArray<FString> QuestIDs;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	bool bIsKeyNPC = false;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	bool bIsPersistent = true;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	FVector HomeLocation;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	FRotator HomeRotation;
	
	UPROPERTY(EditAnywhere, Category = "NPC")
	FDateTime LastSpawnTime;
	
	// State Management
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetNPCRole(ENPCRole NewRole);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetNPCDistrict(ENPCDistrict NewDistrict);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetState(ENPCState NewState);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	FVector GetHomeLocation();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void SetHomeLocation(FVector Location);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	bool IsAvailableForInteraction();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void OnPlayerProximity(ACharacter* Player);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void OnPlayerFar();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void OnDamage(float DamageAmount, AActor* DamageCauser);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void OnDeath();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void OnQuestComplete(FString QuestID);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	float GetReputation();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void AddReputation(float Amount);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void RemoveReputation(float Amount);
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	TEnumAsByte<ENPCState> GetCurrentState();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	TEnumAsByte<ENPCRole> GetNPCRole();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	TEnumAsByte<ENPCDistrict> GetNPCDistrict();
	
	UFUNCTION(BlueprintCallable, Category = "NPC")
	FString GetNPCName();
	
protected:
	// NPC Data
	float Reputation = 0.5f;
	float InteractionCooldown = 0.0f;
	bool bIsInteractable = true;
	bool bIsInDanger = false;
	AActor* Aggressor = nullptr;
	
	// Components
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class UDialogueComponent* DialogueComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class UQuestComponent* QuestComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "NPC")
	class UBlackboardComponent* BlackboardComponent;
	
	// Timers
	FTimerHandle InteractionTimerHandle;
	FTimerHandle DangerTimerHandle;
};