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
#include "Components/CapsuleComponent.h" // For GetCapsuleComponent()
#include "MyCharacter.generated.h"

UCLASS()
class PLAYERCHARACTER_API AMyCharacter : public ACharacter
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
	// stimulus to be used for sight
	UPROPERTY(EditAnywhere, Category = "AI")
	class UAIPerceptionStimuliSourceComponent* SightStimulus;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();
	//stimulus registration function
	void RegisterSightStimulus();

};
