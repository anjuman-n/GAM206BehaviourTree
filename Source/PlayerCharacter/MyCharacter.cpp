// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 90.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//set camera pitch
	APlayerCameraManager* const PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	if (PlayerCameraManager)
	{
		PlayerCameraManager->ViewPitchMin = -30.0f;
		PlayerCameraManager->ViewPitchMax = 10.0f;
	}
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputMapping, 0); // 0 for hieghst priority
		}
	}
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind movement input (calls Move() when IA_Move is triggered)
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
 
		// Bind camera/look input (calls Look() when IA_LookAction is triggered)
		Input->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
 
		// Bind jump input (calls Jump() when IA_Jump is triggered)
		Input->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
	}

}
void AMyCharacter::Move(const FInputActionValue &InputValue)
{
	// Get 2D input vector from Enhanced Input
	FVector2D InputVector = InputValue.Get<FVector2D>();
 
	if (IsValid(Controller))
	{
		// Get the controller's current rotation
		const FRotator Rotation = Controller->GetControlRotation();
		// Isolate yaw rotation (ignore pitch and roll)
		const FRotator YawRotation(0, Rotation.Yaw, 0);
 
		// Calculate forward and right directions relative to yaw
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
 
		// Apply movement input along forward/backward
		AddMovementInput(ForwardDirection, InputVector.Y);
		// Apply movement input along right/left
		AddMovementInput(RightDirection, InputVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue &InputValue)
{
	// Get 2D input vector from Enhanced Input
	FVector2D InputVector = InputValue.Get<FVector2D>();
	if (IsValid(Controller))
	{
		// Apply horizontal (yaw) rotation from input
		AddControllerYawInput(InputVector.X);
		// Apply vertical (pitch) rotation from input
		AddControllerPitchInput(InputVector.Y);
	}
}

void AMyCharacter::Jump()
{
	// Call built-in Unreal Engine jump function
	ACharacter::Jump();
}
//stimulus registration function
void AMyCharacter::RegisterSightStimulus()
{
	SightStimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("Sight Stimulus");// Create the stimulus component
	if (SightStimulus)
	{
		SightStimulus->RegisterForSense(TSubclassOf<UAISense_Sight>()); // Register for sight sense
	}
}