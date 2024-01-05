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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<APlayerCharacter> PlayerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> PickUpSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UTexture2D> ItemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") EItemNames ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (MultiLine = true)) FText ItemDescription;
	friend class APlayerCharacter;

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;

private:

public:
#pragma region Getters&Setters
	
	[[nodiscard]] UFUNCTION(BlueprintCallable) EItemNames GetItemName() const
	{
		return ItemName;
	}
#pragma endregion Getters&Setters
	
};
