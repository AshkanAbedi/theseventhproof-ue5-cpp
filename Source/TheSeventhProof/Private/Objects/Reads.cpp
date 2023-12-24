// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/Reads.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

AReads::AReads()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AReads::Interact_Implementation()
{
	if (!bIsReading)
	{
		AudioComponent->SetSound(ReadSound);
		AudioComponent->Play();
		bIsReading = true;
	}
}
