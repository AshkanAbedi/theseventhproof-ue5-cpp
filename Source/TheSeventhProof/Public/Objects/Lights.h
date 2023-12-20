// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseInteractable.h"
#include "Lights.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UPointLightComponent;
class UAudioComponent;
class USoundCue;

UCLASS()
class THESEVENTHPROOF_API ALights : public ABaseInteractable
{
	GENERATED_BODY()

public:
	ALights();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UPointLightComponent> LightComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> SwitchSound;
	
	virtual void Interact_Implementation() override;
	
};
