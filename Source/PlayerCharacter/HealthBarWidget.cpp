// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

void UHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
    //get progress bar reference
    
}

void UHealthBarWidget::SetHealthPercentage(float const HealthPercent, bool const bIsPlayer)
{
    if (bIsPlayer && PlayerHealthBar)
    {
      PlayerHealthBar->SetPercent(HealthPercent);
    }
    else if (EnemyHealthBar)
    {
      EnemyHealthBar->SetPercent(HealthPercent);
    }
}
