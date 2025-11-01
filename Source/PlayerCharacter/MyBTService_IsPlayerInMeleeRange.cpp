// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_IsPlayerInMeleeRange.h"

UMyBTService_IsPlayerInMeleeRange::UMyBTService_IsPlayerInMeleeRange()
{
    bNotifyBecomeRelevant = true;
    NodeName = "Is Player In Melee Range";

}

void UMyBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
     //get controller and NPC
    ANPCAIController* AICon = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
    ANPCCharacter* NPC = Cast<ANPCCharacter>(AICon->GetPawn());
    //get player character
    ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if(NPC && PlayerChar)
    {
        float Distance = FVector::Dist(NPC->GetActorLocation(), PlayerChar->GetActorLocation());
        if(Distance <= MeleeRange)
        {
            //set blackboard value
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        }
        else
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), false);
        }
    }
}

