// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppParameterMayBeConstPtrOrRef

#include "Objects/Doors.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/Items.h"

ADoors::ADoors()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void ADoors::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->OnItemAddedToInventoryDelegate.AddDynamic(this, &ADoors::Unlocking);
}

void ADoors::Interact_Implementation()
{
	if (bIsToggling) return;

	switch (DoorState)
	{
		case EDoorStates::EDS_StateNormal:
			if (!bIsOpen)
			{
				AudioComponent->SetSound(OpeningSound);
				AudioComponent->Play();
				OpeningDoor();
				DoorState = EDoorStates::EDS_StateNormal;
			}
			else
			{
				AudioComponent->SetSound(ClosingSound);
				AudioComponent->Play();
				ClosingDoor();
				DoorState = EDoorStates::EDS_StateNormal;
			}
			break;
		
		case EDoorStates::EDS_StateLocked:
			AudioComponent->SetSound(LockedSound);
			AudioComponent->Play();
			DoorState = EDoorStates::EDS_StateLocked;
			break;

		case EDoorStates::EDS_StateUnlocking:
			AudioComponent->SetSound(UnlockingSound);
			AudioComponent->Play();
			GetWorld()->GetTimerManager().SetTimer(UnlockTimerHandle, this, &ADoors::OpeningDoor, UnlockingSound->Duration, false);
			// TODO: Clear the timer handle
			DoorState = EDoorStates::EDS_StateNormal;
			break;
	}
}

void ADoors::OpeningDoor()
{
	FOnTimelineFloat TimelineTickDelegate;
	FOnTimelineEvent TimelineFinishedDelegate;
	TimelineTickDelegate.BindUFunction(this, "DoorToggling");
	TimelineFinishedDelegate.BindUFunction(this, "TimelineFinished");
	TimelineComponent->AddInterpFloat(TogglingCurve, TimelineTickDelegate);
	TimelineComponent->SetTimelineLength(ETimelineLengthMode::TL_TimelineLength);
	TimelineComponent->SetPlayRate(1.f);
	TimelineComponent->PlayFromStart();
	AudioComponent->SetSound(OpeningSound);
	AudioComponent->Play();
	bIsToggling = true;
	bIsOpen = true;
	TimelineComponent->SetTimelineFinishedFunc(TimelineFinishedDelegate);
}

void ADoors::ClosingDoor()
{
	FOnTimelineFloat TimelineTickDelegate;
	FOnTimelineEvent TimelineFinishedDelegate;
	TimelineTickDelegate.BindUFunction(this, "DoorToggling");
	TimelineFinishedDelegate.BindUFunction(this, "TimelineFinished");
	TimelineComponent->AddInterpFloat(TogglingCurve, TimelineTickDelegate);
	TimelineComponent->SetTimelineLength(ETimelineLengthMode::TL_TimelineLength);
	TimelineComponent->SetPlayRate(2.5f);
	TimelineComponent->ReverseFromEnd();
	AudioComponent->SetSound(ClosingSound);
	AudioComponent->Play();
	bIsToggling = true;
	bIsOpen = false;
	TimelineComponent->SetTimelineFinishedFunc(TimelineFinishedDelegate);
}

void ADoors::Unlocking()
{
	for (auto Element : CorrespondingItems)
	{
		if (!PlayerCharacter->GetInventory().Contains(Element) || DoorState == EDoorStates::EDS_StateUnlocking)
		{
			return;
		}
	}
	DoorState = EDoorStates::EDS_StateUnlocking;
}

void ADoors::DoorToggling(const float Output) const
{
	switch (DoorType) {
	case EDoorTypes::EDT_Type01:

		StaticMeshComponent->SetRelativeRotation(FRotator(0, Output, 0));
		break;
		
	case EDoorTypes::EDT_Type02:

		StaticMeshComponent->SetRelativeRotation(FRotator(0, 0, Output));
		break;
		
	case EDoorTypes::EDT_Type03:

		StaticMeshComponent->SetRelativeLocation(FVector(Output, 0, 0));
		break;
		
	case EDoorTypes::EDT_Type04:

		StaticMeshComponent->SetRelativeLocation(FVector(0, Output, 0));
		break;
	}
	
}

void ADoors::TimelineFinished()
{
	bIsToggling = false;
}

