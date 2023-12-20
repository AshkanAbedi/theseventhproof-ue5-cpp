// Fill out your copyright notice in the Description page of Project Settings.
#include "Objects/Observables.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AObservables::AObservables()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void AObservables::Interact_Implementation()
{
	// Super::Interact_Implementation();
}

