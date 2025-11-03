// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MeleeAttack.h"
UMyBTTask_MeleeAttack::UMyBTTask_MeleeAttack()
{
    NodeName = "Melee Attack";
}

EBTNodeResult::Type UMyBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    //check from blackboard key if the player is out of melee range then do not attack
    auto const IsInMeleeRange = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
    if(!IsInMeleeRange)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return EBTNodeResult::Succeeded;
    }
    // if the player is in melee range then get AI controller and NPC
    ANPCAIController* AICon = Cast<ANPCAIController>(OwnerComp.GetAIOwner()); // Get the AI controller

    ANPCCharacter* NPC = Cast<ANPCCharacter>(AICon->GetPawn()); // Get the NPC character
    // if the NPC supports the ICombatInterface, cast and call melee attack function
    if(auto* const CombatNPC = Cast<ICombatInterface>(NPC))
    {
        //check if montage has finished playing
        if(MontageHasFinished(NPC))
        {
            CombatNPC->Execute_MeleeAttack(NPC); // Call the MeleeAttack function
        }
        
    }


   // Finish the task and return succeeded
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Type();
}
bool UMyBTTask_MeleeAttack::MontageHasFinished(ANPCCharacter* const NPC)
{
    if(NPC)
    {
        UAnimInstance* AnimInstance = NPC->GetMesh()->GetAnimInstance();
        if(AnimInstance && NPC->AttackMontage)
        {
            return !AnimInstance->Montage_IsPlaying(NPC->AttackMontage);
        }
    }
    return true; // If no NPC or no montage, consider it finished
}