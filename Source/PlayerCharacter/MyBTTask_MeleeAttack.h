// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
//include NPCCharacter to call melee attack function
#include "NPCCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
//
#include "NPCAIController.h"
#include "CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
//
#include "MyBTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERCHARACTER_API UMyBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
private:
	// Check if the montage has finished playing
	bool MontageHasFinished(ANPCCharacter* const NPC);
public:
	// Constructor
	UMyBTTask_MeleeAttack();
	// Execute Task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
