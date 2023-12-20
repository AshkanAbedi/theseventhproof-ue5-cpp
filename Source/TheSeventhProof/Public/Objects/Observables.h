// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseInteractable.h"
#include "Observables.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class THESEVENTHPROOF_API AObservables : public ABaseInteractable
{
	GENERATED_BODY()
public:
	AObservables();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Properties") FText StoryText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties") float StoryDelay;

	virtual void Interact_Implementation() override;
	
};
