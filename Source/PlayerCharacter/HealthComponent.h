// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYERCHARACTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//max health points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	int CurrentHealth = 100;
	// take damage points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	int DamageAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	bool isCanBeDamaged;
	//
	void Die();

public:
	void TakeDamage();
	
	int GetMaxHealth() const; 
	int GetCurrentHealth() const ;
	float GetCurrentHealthPercent(); 
};
