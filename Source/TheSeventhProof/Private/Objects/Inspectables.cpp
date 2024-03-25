// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo
// ReSharper disable CppMemberFunctionMayBeConst

#include "Objects/Inspectables.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Character/PlayerCharacter.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/GameplayStatics.h"


AInspectables::AInspectables()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));
}

void AInspectables::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = StaticMeshComponent->GetComponentTransform();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AInspectables::Interact_Implementation()
{
	if (IsValid(MoveCurve) && IsValid(PlayerCharacter) && PlayerCharacter->PlayerStates == EPlayerState::EPS_Normal)
	{
		FOnTimelineFloat TimelineTickDelegate;
		TimelineTickDelegate.BindUFunction(this, "TimelineStarted");
		TimelineComponent->AddInterpFloat(MoveCurve, TimelineTickDelegate);
		TimelineComponent->SetTimelineLength(ETimelineLengthMode::TL_LastKeyFrame);
		TimelineComponent->SetPlayRate(1.f);
		TimelineComponent->PlayFromStart();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Timeline Started"));
	}
}

void AInspectables::TimelineStarted(const float Output)
{
	const FVector DestPoint = PlayerCharacter->InspectableItem->GetComponentTransform().GetLocation();
	const float LerpX = FMath::Lerp(StartLocation.GetLocation().X, DestPoint.X, Output);
	const float LerpY = FMath::Lerp(StartLocation.GetLocation().Y, DestPoint.Y, Output);
	const float LerpZ = FMath::Lerp(StartLocation.GetLocation().Z, DestPoint.Z, Output);
	StaticMeshComponent->SetWorldLocation(FVector(LerpX, LerpY, LerpZ));
	PlayerCharacter->SetInspectedObject(this);
	PlayerCharacter->MainCamera->SetFieldOfView(FMath::Lerp(80.f, 75.f, Output));
	PlayerCharacter->PostProcessComponent->Settings.DepthOfFieldFocalDistance = FMath::Lerp(0.f, 15.f, Output);
	PlayerCharacter->PlayerStates = EPlayerState::EPS_Inspecting;
}

void AInspectables::ReturnToStart()
{
	if (IsValid(PlayerCharacter) && PlayerCharacter->PlayerStates == EPlayerState::EPS_Inspecting)
	{
		StaticMeshComponent->SetWorldTransform(StartLocation);
		PlayerCharacter->SetInspectedObject(nullptr);
		PlayerCharacter->MainCamera->SetFieldOfView(80.f);
		PlayerCharacter->PostProcessComponent->Settings.DepthOfFieldFocalDistance = 0.f;
		PlayerCharacter->PlayerStates = EPlayerState::EPS_Normal;
	}
}





