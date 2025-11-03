// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthManager.h"

// Sets default values
AHealthManager::AHealthManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void AHealthManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	

}

float AHealthManager::GetHealthPercentage() const
{
    return CurrentHealth / MaxHealth;
}

float AHealthManager::GetMaxHealth() const
{
    return MaxHealth;
}

float AHealthManager::GetCurrentHealth() const
{
    return CurrentHealth;
}

void AHealthManager::SetHealth(float const NewHealth)
{
	CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
}
