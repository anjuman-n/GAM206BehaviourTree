// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
//
#include "NPCAIController.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERCHARACTER_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
	class UAISenseConfig_Sight* SightConfig;
	protected:
	virtual void OnPossess(APawn* InPawn) override;//override the possess function
	
public:
	float SightRadiusLocal;
	explicit ANPCAIController(FObjectInitializer const& ObjectInitializer);//constructor
// Function to set up the sight configuration
	void setupSightConfig();
	// Called when the AI's perception of a target is updated
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
		
};