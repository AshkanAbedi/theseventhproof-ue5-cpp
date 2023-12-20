// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/Items.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Character/PlayerCharacter.h"

AItems::AItems()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AItems::Interact_Implementation()
{
	if (IsValid(GetWorld()->GetFirstPlayerController())) {

		if (IsValid(PickUpSound)) {
			AudioComponent->SetSound(PickUpSound);
			AudioComponent->Play();
		}
		FTimerHandle DestroyTimerHandle;
		Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->AddToInventory(this);
		this->SetActorHiddenInGame(true);
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AItems::DestroyActor, PickUpSound->Duration, false);
	}
}

void AItems::DestroyActor()
{
	Destroy();
}

