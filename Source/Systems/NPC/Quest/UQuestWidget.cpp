#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

/**
 * Quest Widget Blueprint
 * Displays quest information and progress
 */
UCLASS()
class EARTHTHAGAIN_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UQuestWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	// Quest Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FString QuestName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FString QuestDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int32 CurrentStep;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	int32 TotalSteps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	float QuestProgress;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsQuestComplete;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	bool bIsQuestActive;
	
	// Functions
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuest(FString Name, FString Description, int32 Current, int32 Total);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuestProgress(float Progress);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuestComplete(bool bComplete);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void SetQuestActive(bool bActive);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateQuestStep(int32 NewStep);
	
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void CloseQuest();
	
protected:
	// Widget Components
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestNameText;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestDescriptionText;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestStepText;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* QuestProgressBar;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* QuestStatusSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestStatusText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;
	
	// Event Dispatchers
	UFUNCTION(BlueprintAssignable, Category = "Quest")
	FOnQuestClosed OnQuestClosed;
};