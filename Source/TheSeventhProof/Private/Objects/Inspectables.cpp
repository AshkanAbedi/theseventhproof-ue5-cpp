// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo
// ReSharper disable CppMemberFunctionMayBeConst

#include "Objects/Inspectables.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Character/PlayerCharacter.h"


AInspectables::AInspectables()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
}

void AInspectables::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = StaticMeshComponent->GetComponentTransform();
}

void AInspectables::Interact_Implementation()
{
	
	if (IsValid(PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())) && !bIsInspecting)
	{
		const FTransform DestPoint = PlayerCharacter->InspectableItem->GetComponentTransform();
		StaticMeshComponent->SetWorldTransform(DestPoint);
		PlayerCharacter->InspectedObject = this;
		bIsInspecting = true;
	}
}

void AInspectables::ReturnToStart()
{
	if (bIsInspecting && IsValid(PlayerCharacter))
	{
		StaticMeshComponent->SetWorldTransform(StartLocation);
		PlayerCharacter->InspectedObject = nullptr;
		bIsInspecting = false;
		GEngine->AddOnScreenDebugMessage(9, 5.f, FColor::Red, TEXT("ReturnToStart"));
	}
}


