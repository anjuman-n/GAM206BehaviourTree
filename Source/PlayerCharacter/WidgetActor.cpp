// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetActor.h"

// Sets default values
AWidgetActor::AWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	// health bar widget creation
	
	if(IsValid(GameHUDClass))
	{
		GameHUD = CreateWidget<UHealthBarWidget>(GetWorld(), GameHUDClass);
		if(GameHUD)
		{
			GameHUD->AddToViewport();
		}
	}
	
}

// end play	
void AWidgetActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(GameHUD)
	{
		GameHUD->RemoveFromParent();
	}
	Super::EndPlay(EndPlayReason);
}
