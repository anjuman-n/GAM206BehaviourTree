// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthComponent::TakeDamage(int DamageAmount)// Handle taking damage
{
	if(isCanBeDamaged)
	{
		CurrentHealth -= DamageAmount;
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Took %d damage, Current Health: %d"), DamageAmount, CurrentHealth));
		}
		if(CurrentHealth <= 0)
		{
			Die();
		}
	}
}
void UHealthComponent::Die()
{
	// Handle death logic here (e.g., notify the owner actor, play animation, etc.)
	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->Destroy();
	}
}		

