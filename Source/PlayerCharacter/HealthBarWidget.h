// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERCHARACTER_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	private:
	// Health bar progress
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, allowPrivateAccess = true))//	 Bind to ProgressBar named HealthBar in UMG
	class UProgressBar* HealthBar = nullptr;
	public:
	// Function to set health percentage
	virtual void NativeConstruct() override;

	
	void SetHealthPercentage(float const HealthPercent);
};
