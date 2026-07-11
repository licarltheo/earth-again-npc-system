#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * Dialogue Widget Blueprint
 * Displays dialogue options and NPC responses
 */
UCLASS()
class EARTHTHAGAIN_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDialogueWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	// Dialogue Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString NPCName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString CurrentDialogueText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> DialogueOptions;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<int32> NextNodeIDs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float Reputation;
	
	// Functions
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetDialogue(FString Text, TArray<FString> Options, TArray<int32> NextIDs);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetNPCName(FString Name);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetReputation(float NewReputation);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void OnOptionSelected(int32 OptionIndex);
	
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void CloseDialogue();
	
protected:
	// Widget Components
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCNameText;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogueText;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* OptionSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton_0;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton_1;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton_2;
	
	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton_3;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;
	
	// Event Dispatchers
	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueOptionSelected OnDialogueOptionSelected;
	
	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueClosed OnDialogueClosed;
};