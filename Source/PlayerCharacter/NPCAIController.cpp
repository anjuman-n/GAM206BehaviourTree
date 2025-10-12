// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPCCharacter.h"
#include "MyCharacter.h"


//constructor
ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
    setupSightConfig();
    
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

        SetPerceptionComponent (*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT ("Perception Component")));
        SightConfig -> SightRadius = 150.f;
        SightConfig -> LoseSightRadius = SightConfig->SightRadius + 25.f;
        SightConfig->PeripheralVisionAngleDegrees = 90.f;
        SightConfig->SetMaxAge(5.f);
        SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetPerceptionUpdated);
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
        
        GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
        if(GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("NPC Perception Updated: %s, Successfully Sensed: %s"), *Actor->GetName(), Stimulus.WasSuccessfullySensed() ? TEXT("True") : TEXT("False")));

    }
}