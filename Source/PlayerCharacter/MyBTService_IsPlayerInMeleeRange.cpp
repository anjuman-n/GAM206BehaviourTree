// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_IsPlayerInMeleeRange.h"

UMyBTService_IsPlayerInMeleeRange::UMyBTService_IsPlayerInMeleeRange()
{
    bNotifyBecomeRelevant = true; // Enable notification when the service becomes relevant

    NodeName = "Is Player In Melee Range";

}

void UMyBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
     //get controller and NPC
    ANPCAIController* AICon = Cast<ANPCAIController>(OwnerComp.GetAIOwner());

    ANPCCharacter* NPC = Cast<ANPCCharacter>(AICon->GetPawn()); // Get the NPC character
    //get player character
    ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);// Get the player character

    if(NPC && PlayerChar)
    {
        float Distance = FVector::Dist(NPC->GetActorLocation(), PlayerChar->GetActorLocation()); // Calculate distance between NPC and player
       
        if(Distance <= MeleeRange)
        {
            //set blackboard value
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true); // Set blackboard key to true if within melee range
        }
        else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false); // Set blackboard key to false if out of melee range
        }
    }
}

