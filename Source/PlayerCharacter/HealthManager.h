// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthManager.generated.h"

UCLASS()
class PLAYERCHARACTER_API AHealthManager : public AActor
{
	GENERATED_BODY()
	private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	class UHealthBarWidget* HealthBarWidget;
	//editblueprint max health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;
	//current health
	float CurrentHealth = 100.f;

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	public:
	// Sets default values for this actor's properties
	AHealthManager();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// get health percentage
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercentage() const;
	// Get MAx health
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const;
	// Get Current Health
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() const;
	// Set health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float const NewHealth);	


};
