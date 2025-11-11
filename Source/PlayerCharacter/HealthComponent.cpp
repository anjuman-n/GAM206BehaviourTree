// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}
// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TakeDamage()// Handle taking damage
{
	if(isCanBeDamaged)
	{
		CurrentHealth = CurrentHealth>=0 ? CurrentHealth - DamageAmount : 0;
		if(CurrentHealth <= 0)
		{
			Die();
		}
		if(GEngine) // For debugging purposes
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Took %d damage, Current Health: %d"), DamageAmount, CurrentHealth));
	}
}
int UHealthComponent::GetMaxHealth() const
{
    return MaxHealth;//	 return max health points
}
int UHealthComponent::GetCurrentHealth() const 
{
	return CurrentHealth;// return current health points
}
float UHealthComponent::GetCurrentHealthPercent()
{
	return static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth); // return current health percentage
}
void UHealthComponent::Die()
{
	// Handle death logic here (e.g., notify the owner actor, play animation, etc.)
	AActor* Owner = GetOwner();
	if(Owner)
	{
		//owner die after 2 seconds
		//Call die montage animation here if needed
		//then die after delay
		Owner->SetLifeSpan(2.0f);
		// or die instantly 
		//owner->Destroy();
		
	}
}		

