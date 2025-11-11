// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"
#include "MyCharacter.h"   	 // Include MyCharacter header for casting
// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//set box collider for punch socket
	PunchCollisionBox = CreateDefaultSubobject<UBoxComponent>("PunchCollisionBox");
	if(PunchCollisionBox)
	{
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, 
			EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		PunchCollisionBox->AttachToComponent(GetMesh(), AttachRules, "Punch_joint");
		// Initialize box size
		PunchCollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		PunchCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AttackEnd();
	}
		//
	// Automatically find the WidgetActor in the level
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWidgetActor::StaticClass(), FoundActors);

    if (FoundActors.Num() > 0)
    {
        WidgetActorReference = Cast<AWidgetActor>(FoundActors[0]);
    }
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	// register punch collider overlap events
	if(PunchCollisionBox)
	{
		PunchCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ANPCCharacter::OnPunchCollisionBeginOverlap);
		PunchCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ANPCCharacter::OnPunchCollisionEndOverlap);
		
	}

}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ANPCCharacter::GetBehaviorTreeComponent() const
{
	return Tree;
}

int ANPCCharacter::MeleeAttack_Implementation()
{
	if(AttackMontage)
	{
		AttackStart();
		PlayAnimMontage(AttackMontage);
	}
    return 0;
}

void ANPCCharacter::OnPunchCollisionBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
		
	if(OtherActor == this)
	{	
		return;
	}
	//if other actor is not null and it's player character then apply damage
	if(OtherActor)
	{
		if(GEngine) // For debugging purposes
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Punch Overlap with: %s"), *OtherActor->GetName()));

		AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
		if(MyCharacter)
		{
			//get health component of player and apply damage
			UHealthComponent* HealthComp = MyCharacter->FindComponentByClass<UHealthComponent>();
			if(HealthComp)
			{
				HealthComp->TakeDamage();
				// get widget actor in the world to update health bar
				if(GEngine) // For debugging purposes
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player Current Health: %d"), HealthComp->GetCurrentHealth()));
				// Update health bar widget
				if (WidgetActorReference)
				{
					UHealthBarWidget* HealthBar = WidgetActorReference->GameHUD;
					if (HealthBar)
					{
						HealthBar->SetHealthPercentage(HealthComp->GetCurrentHealthPercent(), true);
					}
				}
			}
		}
	}
}

void ANPCCharacter::OnPunchCollisionEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	AttackEnd();
}

void ANPCCharacter::AttackStart()
{
	//enable collision on punch box	
	if(PunchCollisionBox)
	{
		PunchCollisionBox->SetCollisionProfileName("Punch");//set collision profile to weapon to detect hit
		PunchCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ANPCCharacter::AttackEnd()
{
	if(PunchCollisionBox)
	{
		PunchCollisionBox->SetCollisionProfileName("Punch");//set collision profile to weapon to detect hit
		PunchCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
