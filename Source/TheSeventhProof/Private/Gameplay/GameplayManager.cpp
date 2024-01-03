// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameplayManager.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter.h"
#include "Objects/Items.h"
#include "Objects/Doors.h"

AGameplayManager::AGameplayManager()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
}

void AGameplayManager::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItems::StaticClass(), ItemActors);
	for (const auto ItemActor : ItemActors)
	{
		Items.Add(Cast<AItems>(ItemActor));
	}
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoors::StaticClass(), DoorsActors);
	
}

void AGameplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

