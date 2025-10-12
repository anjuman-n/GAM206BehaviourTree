// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindRandomLocation.h"

UMyBTTask_FindRandomLocation::UMyBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "Find Random Location in Navigation Mesh";
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
    if(auto* controller = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
    {
        if(auto* npc = Cast<ANPCCharacter>(controller->GetPawn()))
        {
            // Get the navigation system
            UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(npc->GetWorld());
            if (NavSys == nullptr)
            {
                return EBTNodeResult::Failed;
            }

            // Find a random reachable point within the specified radius
            FNavLocation RandomLocation;
            bool bFound = NavSys->GetRandomReachablePointInRadius(npc->GetActorLocation(), SearchRadius, RandomLocation);
            if (bFound)
            {
                // Set the found location in the blackboard
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomLocation.Location);
               
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                return EBTNodeResult::Succeeded;
            }
        }
 
    }
      return EBTNodeResult::Failed;

}