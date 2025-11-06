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
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	int CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	bool isCanBeDamaged;
	//
	void Die();

public:
	void TakeDamage(int DamageAmount);
	
};
