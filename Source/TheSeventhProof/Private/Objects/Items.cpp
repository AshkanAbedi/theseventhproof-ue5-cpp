// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/Items.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AItems::AItems()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AItems::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AItems::Interact_Implementation()
{
	if (IsValid(PlayerCharacter) && IsValid(PickUpSound)) {
		AudioComponent->SetSound(PickUpSound);
		AudioComponent->Play();
		PlayerCharacter->AddToInventory(this);
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
	}
}

