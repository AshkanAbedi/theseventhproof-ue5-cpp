// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseInteractable.h"
#include "Items.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;
class USoundCue;
class APlayerCharacter;

UCLASS()
class THESEVENTHPROOF_API AItems : public ABaseInteractable
{
	GENERATED_BODY()

public:
	AItems();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> PickUpSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UTexture2D> ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") FText ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (MultiLine = true)) FText ItemDescription;

	virtual void Interact_Implementation() override;
	void DestroyActor();
	
private:
	
};
