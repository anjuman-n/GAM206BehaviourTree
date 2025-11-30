// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAudioComponent.h"

// Sets default values for this component's properties
UMyAudioComponent::UMyAudioComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UMyAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (AudioClip)
    {
        InternalAudioComponent = NewObject<UAudioComponent>(this);
        InternalAudioComponent->RegisterComponent();
        InternalAudioComponent->AttachToComponent(
            GetOwner()->GetRootComponent(),
            FAttachmentTransformRules::KeepRelativeTransform
        );
        InternalAudioComponent->SetSound(AudioClip);
    }
}


// Called every frame
void UMyAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UMyAudioComponent::PlayAudio()
{
//debug message
	if (GEngine)
	{
		// InternalAudioComponent->IsPlaying()check debug
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("PlayAudio called %b"), InternalAudioComponent->IsPlaying());
	}

	if (InternalAudioComponent && AudioClip)
    {
        if (!InternalAudioComponent->IsPlaying())
        {
            InternalAudioComponent->Play();
        }
    }
}
// alternative way to play audio using GameplayStatics
void UMyAudioComponent::PlayAudioClip()
{
	if (AudioClip && GetOwner())
	{
		UGameplayStatics::PlaySoundAtLocation(this, AudioClip, GetOwner()->GetActorLocation());
	}
}
//stop audio clip
void UMyAudioComponent::StopAudio()
{
	if (InternalAudioComponent && InternalAudioComponent->IsPlaying())
	{
		InternalAudioComponent->Stop();
	}
}