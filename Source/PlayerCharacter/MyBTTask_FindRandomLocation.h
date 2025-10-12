// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "NPCAIController.h"
#include "NPCCharacter.h"
#include "MyBTTask_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERCHARACTER_API UMyBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 1500.0f;
public:
	explicit UMyBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
