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
class APlayerCharacter;

UCLASS()
class THESEVENTHPROOF_API AInspectables : public ABaseInteractable
{
	GENERATED_BODY()

public:
	AInspectables();
	bool bIsInspecting;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components") float InspectRotateSpeed;
	void ReturnToStart();
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound") TObjectPtr<USoundCue> SoundCue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player") TObjectPtr<APlayerCharacter> PlayerCharacter;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") FTransform StartLocation;

	virtual void Interact_Implementation() override;
	virtual void BeginPlay() override;

private:
	
};
