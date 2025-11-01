// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindRandomLocation.h"

UMyBTTask_FindRandomLocation::UMyBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "Find Random Location in Navigation Mesh";// Set the name of the node
}
// ExecuteTask is called when the task is executed
EBTNodeResult::Type UMyBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Get the AI controller and the controlled pawn
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (AICon == nullptr)
    {
        return EBTNodeResult::Failed;
    }
    // Get the controlled pawn and its npc character
    if(auto* controller = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))// Ensure the AI controller is of type ANPCAIController
    {
        if(auto* npc = Cast<ANPCCharacter>(controller->GetPawn()))// Ensure the controlled pawn is of type ANPCCharacter
        {
            // Get the navigation system
            UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(npc->GetWorld());// Get the current navigation system
            if (NavSys == nullptr)
            {
                return EBTNodeResult::Failed; // If the navigation system is null, fail the task
            }
            // Find a random reachable point within the specified radius
            FNavLocation RandomLocation;
            bool bFound = NavSys->GetRandomReachablePointInRadius(npc->GetActorLocation(), SearchRadius, RandomLocation); // Try to find a random reachable point
            if (bFound)
            {
                // Set the found location in the blackboard
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomLocation.Location); // Set the random location in the blackboard
               
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // Finish the task successfully
                return EBTNodeResult::Succeeded;// Return success
            }
        }
    }
      return EBTNodeResult::Failed;//
}