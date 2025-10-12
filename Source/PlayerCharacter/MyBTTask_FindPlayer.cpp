// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindPlayer.h"
#include "MyCharacter.h"


// constructor
UMyBTTask_FindPlayer::UMyBTTask_FindPlayer(FObjectInitializer const& ObjectInitializer) 
{
    NodeName = "Find Player Location";
}

// override the execute task function
EBTNodeResult::Type UMyBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    FName KeyName = "TargetLocation";
    //get player
    
    if(auto* const Player = UGameplayStatics::GetPlayerCharacter (GEngine->GameViewport->GetWorld(),  0))
    {
        auto const PlayerLocation = Player->GetActorLocation();
        
        if (SearchRandomLocation)
        {
            FNavLocation Loc;
            // get the naviagation system and generate a random location near the player
            if(auto* const NavSys = UNavigationSystemV1::GetCurrent(GEngine->GameViewport->GetWorld()))
            {
                // try to get a random location near the player
                if (NavSys->GetRandomPointInNavigableRadius(PlayerLocation, 150.f,Loc))
                {
                    OwnerComp.GetBlackboardComponent() -> SetValueAsVector(KeyName, Loc.Location);
                    
                    return EBTNodeResult::Succeeded;
                }
            }
            
        }
        else
        {
            OwnerComp.GetBlackboardComponent() -> SetValueAsVector(KeyName, PlayerLocation);
            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}