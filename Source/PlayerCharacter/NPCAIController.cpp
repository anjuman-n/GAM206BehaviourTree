// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPCCharacter.h"
#include "MyCharacter.h"


//constructor
ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
    setupSightConfig();
    if(GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Sight Config created successfully"));

    
}
//override the possess function
void ANPCAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    //You can initialize your blackboard and behavior tree here
    if(ANPCCharacter* NPC = Cast<ANPCCharacter>(InPawn))
    {
        if(UBehaviorTree* const BT = NPC->GetBehaviorTreeComponent())
        {
            UBlackboardComponent* BlackboardComp;
            UseBlackboard(BT->BlackboardAsset, BlackboardComp);
            Blackboard = BlackboardComp;
            RunBehaviorTree(BT);
        }
    }
}
//
// Function to set up the sight configuration
void ANPCAIController::setupSightConfig()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    if (SightConfig)
    {
        if(GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Sight Config created successfully"));

        SetPerceptionComponent (*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT ("Perception Component")));// Create and set the perception component
        SightConfig -> SightRadius = 600.f;// Set the sight radius
        SightConfig -> LoseSightRadius = SightConfig->SightRadius + 25.f;// Set the lose sight radius
        SightConfig->PeripheralVisionAngleDegrees = 90.f;// Set the peripheral vision angle
        SightConfig->SetMaxAge(5.f);// Set the max age of the sight stimulus
        SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;// Configure to detect enemies
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetPerceptionUpdated);// Bind the perception update function
        GetPerceptionComponent() ->ConfigureSense(*SightConfig);
    }
    else
    {
        if(GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sight Config is null in NPC AI Controller"));
    }
}
// Called when the AI's perception of a target is updated
void ANPCAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    
    if(auto* const NPC = Cast<AMyCharacter>(Actor))
    {
        
        GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());// Update the blackboard key based on whether the player is sensed
        if(GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("NPC Perception Updated: %s, Successfully Sensed: %s"),
             *Actor->GetName(), Stimulus.WasSuccessfullySensed() ? TEXT("True") : TEXT("False")));

    }
}