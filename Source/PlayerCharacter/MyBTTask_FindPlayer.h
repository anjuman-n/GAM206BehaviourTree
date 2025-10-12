// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "NPCCharacter.h"
#include "NPCAIController.h"
#include "MyBTTask_FindPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERCHARACTER_API UMyBTTask_FindPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	// Search radius for finding a random location
	protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool SearchRandomLocation = false;
	// Radius within which to search for a random location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "SearchRandomLocation", ClampMin = "0.0"))
	float SearchRadius = 200.0f;

public:
	explicit UMyBTTask_FindPlayer(FObjectInitializer const& ObjectInitializer);//	constructor
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;// override the execute task function

	
};
