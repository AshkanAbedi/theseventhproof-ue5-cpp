// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/LineTraceComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/InteractInterface.h"

ULineTraceComponent::ULineTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void ULineTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &ULineTraceComponent::TraceTimer, TraceTimerCount, true);
}

void ULineTraceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);
}

void ULineTraceComponent::TraceTimer()
{
	bHitSomething = GetWorld()->LineTraceSingleByChannel(HitResult, Source->GetComponentLocation(), Source->GetComponentLocation() + (Source->GetForwardVector() * TraceDistance), ECC_Visibility, TraceParams);
if (bHitSomething)
	{
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			IInteractInterface::Execute_Interact(HitResult.GetActor());
		}
	}
}

void ULineTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

