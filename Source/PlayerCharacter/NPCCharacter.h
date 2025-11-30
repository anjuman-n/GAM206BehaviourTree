// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
//import combat interface
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
//import health component
//box component
#include "Components/BoxComponent.h"
//include character header file	
//
#include "HealthComponent.h"
//
// include widget actor
#include "WidgetActor.h"
//widget include
#include "HealthBarWidget.h"
#include "WidgetActor.h"
//
#include "NPCCharacter.generated.h"


//forward declaration my character
class AMyCharacter;

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
	//health component
	//create NPC box collider component to receive damage
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;
	//	let's create a box collider component on the punch socket to detect hit
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider component")
	class UBoxComponent* PunchCollisionBox;
	////get widget actor reference from blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	AWidgetActor* WidgetActorReference;


public:	
// find radius for 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sight")
	float SightRadius = 100.f;
	// attack montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* AttackMontage;
	// die montage
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* DieMontage;
	ANPCCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//Get the behavior tree component prototype
	UBehaviorTree* GetBehaviorTreeComponent() const;
	// interface mellee attack function implementation
	int MeleeAttack_Implementation() override;
	// begin overlap collosinn function for punch collider
	UFUNCTION()
	void OnPunchCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// end overlap collision function for punch collider
	UFUNCTION()
	void OnPunchCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//attack start	
	void AttackStart();
	//attack end	
	void AttackEnd();	
	// interface die function implementation
	void Die_Implementation() override;	


};
