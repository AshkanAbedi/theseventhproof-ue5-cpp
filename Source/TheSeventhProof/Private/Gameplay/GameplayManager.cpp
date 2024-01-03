// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameplayManager.h"

AGameplayManager::AGameplayManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameplayManager::BeginPlay()
{
	Super::BeginPlay();
}

void AGameplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

