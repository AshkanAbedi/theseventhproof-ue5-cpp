// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/Reads.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AReads::AReads()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AReads::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AReads::Interact_Implementation()
{
	if (IsValid(PlayerCharacter) && PlayerCharacter->PlayerStates == EPlayerState::EPS_Normal)
	{
		AudioComponent->SetSound(ReadSound);
		AudioComponent->Play();
		PlayerCharacter->PlayerStates = EPlayerState::EPS_Reading;
	}
}
