// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
//
#include "HealthBarWidget.h"
//
#include "WidgetActor.generated.h"

UCLASS()
class PLAYERCHARACTER_API AWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidgetActor();
	// progress bar widget reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UHealthBarWidget> GameHUDClass = nullptr;
	
	// health bar widget instance

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UHealthBarWidget* GameHUD;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//end play
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	
	

};
