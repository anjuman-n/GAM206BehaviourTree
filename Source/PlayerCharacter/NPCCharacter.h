// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
//import combat interface
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
//
#include "NPCCharacter.generated.h"

UCLASS()
class PLAYERCHARACTER_API ANPCCharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//add behavior tree component and blackboard component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* Tree; // set in editor


public:	
	// attack montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage;

	ANPCCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Get the behavior tree component prototype
	UBehaviorTree* GetBehaviorTreeComponent() const;
	// interface mellee attack function implementation
	int MeleeAttack_Implementation() override;


};
