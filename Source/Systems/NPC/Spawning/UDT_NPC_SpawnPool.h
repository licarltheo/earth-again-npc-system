#pragma once

#include "CoreMinimal.h"
#include "GameplayTaskComponent.generated.h"
#include "DT_NPC_SpawnPool.generated.h"

/**
 * Spawn Pool Data Structure
 */
USTRUCT(BlueprintType)
struct FSpawnPoolData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TEnumAsByte<ENPCDistrict> District;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TEnumAsByte<ENPCRole> RolePool;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TArray<FString> NPCTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TArray<FVector> SpawnPoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	int32 MaxPopulation = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	float SpawnRate = 60.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime MorningStart = FDateTime(2026, 7, 10, 06, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime MorningEnd = FDateTime(2026, 7, 10, 12, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime AfternoonStart = FDateTime(2026, 7, 10, 12, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime AfternoonEnd = FDateTime(2026, 7, 10, 16, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime EveningStart = FDateTime(2026, 7, 10, 16, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime EveningEnd = FDateTime(2026, 7, 10, 22, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime NightStart = FDateTime(2026, 7, 10, 22, 0, 0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	FDateTime NightEnd = FDateTime(2026, 7, 10, 06, 0, 0);
};

/**
 * NPC Spawn Pool Data Asset
 * Contains spawn pool data for a district
 */
UCLASS()
class EARTHTHAGAIN_API UDT_NPC_SpawnPool : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UDT_NPC_SpawnPool();
	
	// Spawn Pool Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TArray<FSpawnPoolData> SpawnPools;
	
	// Persistent NPCs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TArray<FString> KeyNPCNames;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TMap<FString, FVector> KeyNPCLocations;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPool")
	TMap<FString, FRotator> KeyNPCRotations;
	
	// Functions
	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
	FSpawnPoolData GetSpawnPool(ENPCDistrict District, ENPCRole RolePool);
	
	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
	bool IsPersistentNPC(FString NPCName);
	
	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
	FVector GetPersistentNPCLocation(FString NPCName);
	
	UFUNCTION(BlueprintCallable, Category = "SpawnPool")
	FRotator GetPersistentNPCRotation(FString NPCName);
};