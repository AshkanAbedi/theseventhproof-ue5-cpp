// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseInteractable.h"
#include "Inspectables.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;
class USoundCue;
class UTimelineComponent;
class UCurveFloat;
class APlayerCharacter;

UCLASS()
class THESEVENTHPROOF_API AInspectables : public ABaseInteractable
{
	GENERATED_BODY()

public:
	AInspectables();
	// bool bIsInspecting;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound") TObjectPtr<USoundCue> SoundCue;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UTimelineComponent> TimelineComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline") TObjectPtr<UCurveFloat> MoveCurve;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") FTransform StartLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components") float InspectRotateSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player") TObjectPtr<APlayerCharacter> PlayerCharacter;
	friend class APlayerCharacter;

	virtual void Interact_Implementation() override;
	virtual void BeginPlay() override;
	UFUNCTION() void TimelineStarted(const float Output);
	void ReturnToStart();

private:
	
};
