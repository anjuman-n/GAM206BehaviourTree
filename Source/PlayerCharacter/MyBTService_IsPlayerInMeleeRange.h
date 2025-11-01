// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
//includes
#include "NPCCharacter.h"
#include "NPCAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
//
#include "MyBTService_IsPlayerInMeleeRange.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERCHARACTER_API UMyBTService_IsPlayerInMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	private:
	// uproperty edit anywhere for melee range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta = (AllowPrivateAccess = "true"))
	float MeleeRange = 100.f;
	public:	
	UMyBTService_IsPlayerInMeleeRange();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};