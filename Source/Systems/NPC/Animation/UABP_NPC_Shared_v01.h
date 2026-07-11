#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABP_NPC_Shared_v01.generated.h"

/**
 * NPC Animation Blueprint
 * Shared animation blueprint for all NPCs
 */
UCLASS()
class EARTHTHAGAIN_API UABP_NPC_Shared_v01 : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABP_NPC_Shared_v01();
	
	// Animation Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> IdleMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> WalkMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> RunMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> GestureMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> EmotionMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> DangerMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> WorkMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> SchoolMontages;
	
	// Blend Spaces
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UBlendSpace* BlendSpace_Gait;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UBlendSpace* BlendSpace_Expression;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UBlendSpace* BlendSpace_Speed;
	
	// Animation Slots
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FName SlotName_Gesture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FName SlotName_Emotion;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	FName SlotName_Danger;
	
	// Variables
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float WalkSpeed;
	
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float RunSpeed;
	
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float Happiness;
	
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float Sadness;
	
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float Anger;
	
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float Speed;
	
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	TEnumAsByte<ENPCState> CurrentState;
	
	// Functions
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayIdleAnimation();
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayWalkAnimation();
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayRunAnimation();
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayGestureAnimation(FString GestureName);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayEmotionAnimation(FString EmotionName);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayDangerAnimation(FString DangerName);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayWorkAnimation(FString WorkType);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlaySchoolAnimation(FString SchoolType);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateBlendSpaceGait(float NewWalkSpeed, float NewRunSpeed);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateBlendSpaceExpression(float NewHappiness, float NewSadness, float NewAnger);
	
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void UpdateBlendSpaceSpeed(float NewSpeed);
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};