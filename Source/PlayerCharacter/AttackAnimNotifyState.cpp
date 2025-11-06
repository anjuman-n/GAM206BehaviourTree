// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float TotalDuration)
{
    if(MeshComp && MeshComp->GetOwner())// Check if MeshComp and its owner are valid
    {
       if(AMyCharacter* const PlayerCharacter = Cast<AMyCharacter>(MeshComp->GetOwner()))
       {
            PlayerCharacter->Attack();
       }
    }
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
      if(MeshComp && MeshComp->GetOwner())// Check if MeshComp and its owner are valid
    {
       if(AMyCharacter* const PlayerCharacter = Cast<AMyCharacter>(MeshComp->GetOwner()))
       {
            PlayerCharacter->AttackEnd();
       }
    }
}
