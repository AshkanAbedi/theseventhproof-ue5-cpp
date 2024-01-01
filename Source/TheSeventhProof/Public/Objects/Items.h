// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseInteractable.h"
#include "States/ItemNames.h"
#include "Items.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;
class USoundCue;
class UTexture2D;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") EItemNames ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (MultiLine = true)) FText ItemDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player") TObjectPtr<APlayerCharacter> PlayerCharacter;
	friend class APlayerCharacter;

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;

public:
#pragma region Getters&Setters
	
	[[nodiscard]] UFUNCTION(BlueprintCallable) EItemNames GetItemName()
	{
		return ItemName;
	}

	[[nodiscard]] UFUNCTION(BlueprintCallable) TObjectPtr<UTexture2D> GetItemIcon()
	{
		return ItemIcon;
	}
#pragma endregion Getters&Setters

private:
	
};
