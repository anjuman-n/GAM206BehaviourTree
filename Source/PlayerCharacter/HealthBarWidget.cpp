// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

void UHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UHealthBarWidget::SetHealthPercentage(float const HealthPercent)
{
    if (HealthBar)
    {
      //  HealthBar->SetPercent(HealthPercent);
    }
}
