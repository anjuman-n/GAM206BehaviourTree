// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
//import my character header
#include "MyCharacter.h"
//
#include "AttackAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERCHARACTER_API UAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	private:
	// Store original collision settings
	
	public:
	// Override NotifyBegin and NotifyEnd functions
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	// Override NotifyEnd function
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
