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
class APlayerCharacter;

UCLASS()
class THESEVENTHPROOF_API AReads : public ABaseInteractable
{
	GENERATED_BODY()
public:
	AReads();
	// UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") bool bIsReading;
	
#pragma region Getters&Setters
	[[nodiscard]] TObjectPtr<UTexture2D> GetReadImage() const
	{
		return ReadImage;
	}

	[[nodiscard]] FText GetDescription() const
	{
		return Description;
	}
#pragma endregion Getters&Setters

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> ReadSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UTexture2D> ReadImage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") FText Description;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player") TObjectPtr<APlayerCharacter> PlayerCharacter;
	friend class APlayerCharacter;

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	
private:
	
};
