// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo

#include "Objects/BaseInteractable.h"

ABaseInteractable::ABaseInteractable()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseInteractable::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, TEXT("THIS IS AN INTERACTABLE OBJECT"));
}


