// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h" // For GetCharacterMovement()
#include "EnhancedInputComponent.h"       // For UEnhancedInputComponent
#include "EnhancedInputSubsystems.h"      // For UEnhancedInputLocalPlayerSubsystem
#include "InputActionValue.h"             // For FInputActionValue (used in input callbacks)
#include "Perception/AIPerceptionStimuliSourceComponent.h" // For UAIPerceptionStimuliSourceComponent
#include "Perception/AISense_Sight.h" // For UAISense_Sight
//
// include UUserWidget
#include "HealthBarWidget.h"
// include health component
#include "HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
// include widget actor
//audio component
#include "MyAudioComponent.h"
//

#include "WidgetActor.h"
//
//
#include "Components/CapsuleComponent.h" // For GetCapsuleComponent()
//include box component
#include "Components/BoxComponent.h"
//import combat interface
#include "CombatInterface.h"
//npc character header
#include "NPCCharacter.h"
//
#include "MyCharacter.generated.h"

UCLASS()
class PLAYERCHARACTER_API AMyCharacter : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
 
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	// Enhanced Input Mapping Context (class UInputMappingContext*, appears in Blueprint under EnhancedInput)
	UPROPERTY(EditAnywhere,  Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;
	// Character movement input (class UInputAction*, appears in Blueprint under EnhancedInput)
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Move; // forward declared in Blueprint under EnhancedInput
 
	// Jump action input (class UInputAction*, appears in Blueprint under EnhancedInput)
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Jump;

	// Camera/look input (class UInputAction*, appears in Blueprint under EnhancedInput)
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Look;
  // Jump action input (class UInputAction*, appears in Blueprint under EnhancedInput)
    UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* IA_Attack;
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
    class UInputAction* IA_Block;
    //animation montage
    
    UPROPERTY(EditAnywhere, Category = "Animation")
    class UAnimMontage* AttackMontage;
	//Block montage when attack ends
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* BlockMontage;
	// die montage
	UPROPERTY(EditAnywhere, Category = "Animation")
	class UAnimMontage* DieMontage;
    //
    int AttackComboCount = 0;
	// stimulus to be used for sight
	UPROPERTY(EditAnywhere, Category = "AI")
	class UAIPerceptionStimuliSourceComponent* SightStimulus;

	// let's create a box collider component on the sword socket to detect hit
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collider component")
	class UBoxComponent* SwordCollisionBox;

	//get widget actor reference from blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	AWidgetActor* WidgetActorReference;
	// audio component array

	// get sword audio component
	UMyAudioComponent* AudioCompSword = nullptr;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();

	//	callback for montage end
    UFUNCTION()
    void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	//block montage function
	UFUNCTION(BlueprintCallable)
	void Block();	
	//flag for attack
    bool bIsAttacking = false;
    // handle notify montage animation end
    UFUNCTION()
    void HandleMontageBeginNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
 
	//get attack montage
	
	//stimulus registration function
	void RegisterSightStimulus();
	//
	void AttackStart();
	void AttackEnd();
	// overlap function for sword collider
	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// overlap end function for sword collider
	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
			//attack function
	
	void Attack_Implementation();
	// interface die function implementation
	void Die_Implementation() override;	
};
