// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseInteractable.h"
#include "Reads.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;
class USoundCue;
class UTexture2D;

UCLASS()
class THESEVENTHPROOF_API AReads : public ABaseInteractable
{
	GENERATED_BODY()
public:
	AReads();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> PickUpSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UTexture2D> ReadImage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") FText Description;

	virtual void Interact_Implementation() override;
	
private:
	
	
};
