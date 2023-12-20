// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Lights.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

ALights::ALights()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightComponent"));
	LightComponent->SetupAttachment(SceneComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void ALights::Interact_Implementation()
{
	if (LightComponent->IsVisible()) {
		LightComponent->SetVisibility(false);
	}
	else
	{
		LightComponent->SetVisibility(true);
	}
	AudioComponent->SetSound(SwitchSound);
	AudioComponent->Play();
}
