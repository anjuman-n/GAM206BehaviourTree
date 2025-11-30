// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//for playing audio
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
//
#include "MyAudioComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYERCHARACTER_API UMyAudioComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//get audio clip
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundBase* AudioClip;
	UPROPERTY()
	UAudioComponent* InternalAudioComponent;

public:	
	// Sets default values for this component's properties
	UMyAudioComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//play audio clip
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayAudio();
	// another way to play audio GameplayStatics
	//UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayAudioClip();
	//stop audio clip
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopAudio();
};
