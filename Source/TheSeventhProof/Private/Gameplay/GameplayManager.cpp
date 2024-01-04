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
// 	PlayerCharacter->OnItemAddedToInventoryDelegate.AddDynamic(this, &AGameplayManager::Unlocking);
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItems::StaticClass(), ItemActors);
// 	for (const auto ItemActor : ItemActors)
// 	{
// 		Items.Add(Cast<AItems>(ItemActor));
// 	}
// 	// for (const auto Item : Items)
// 	// {
// 	// 	Item->OnItemPickedUp.AddDynamic(this, &AGameplayManager::Unlocking);
// 	// }
//
// 	
// 	
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoors::StaticClass(), DoorsActors);
// 	for (const auto DoorActor : DoorsActors)
// 	{
// 		Doors.Add(Cast<ADoors>(DoorActor));
// 	}
// }

// void AGameplayManager::Unlocking()
// {
// 	for (const auto Door : Doors)
// 	{
// 		if (PlayerCharacter->GetInventory().Contains(Door->GetCorrespondingItems()))
// 		{
// 			Door->DoorState = EDoorStates::EDS_StateUnlocking;
// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Unlocking"));
// 		}
// 	}
}

void AGameplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



