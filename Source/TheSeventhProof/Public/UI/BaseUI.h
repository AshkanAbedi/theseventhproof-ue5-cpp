// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseUI.generated.h"

class APlayerCharacter;
class APlayerController;
class UBaseHUD;
class UBaseInventory;
class AObservables;
class ADoors;
class ALights;
class AItems;
class AInspectables;
class AReads;
class UTexture2D;

UCLASS()
class THESEVENTHPROOF_API ABaseUI : public AHUD
{
	GENERATED_BODY()
	
public:
	ABaseUI();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly) TObjectPtr<APlayerCharacter> PlayerCharacter;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly) TObjectPtr<APlayerController> PlayerController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<UClass*> InteractableObjects;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TArray<UTexture2D*> InteractableObjectIcons;
	UPROPERTY(EditAnywhere) TSubclassOf<UBaseHUD> BaseHUDClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UBaseInventory> BaseInventoryClass;
	UPROPERTY() TObjectPtr<UBaseHUD> BaseHUD;
	UPROPERTY() TObjectPtr<UBaseInventory> BaseInventory;
	UPROPERTY() TObjectPtr<AObservables> Observable;
	UPROPERTY() TObjectPtr<ADoors> Door;
	UPROPERTY() TObjectPtr<ALights> Light;
	UPROPERTY() TObjectPtr<AItems> Item;
	UPROPERTY() TObjectPtr<AInspectables> Inspectable;
	UPROPERTY() TObjectPtr<AReads> Read;

protected:
	UFUNCTION() void OnSeeingInteractable(UClass* InteractableType);
	UFUNCTION() void OnInteracting(AActor* InteractedObject);
	UFUNCTION() void OnCancelInput();
	UFUNCTION() void OnInventoryInput();
	void SetCrosshairIcon(const int Index, const FVector2d Size);
	void ClearCrosshairIcon();
	void SetPromptText(const FText& Text, const float Duration);
	void ClearPromptText();
	void SetReadingImage(UTexture2D* Image);
	void ClearReadingImage();

private:
	bool bInventoryPanel = false;
	UClass* TracedObjectClass;
	UClass* InteractedObjectClass;
	FTimerHandle TextTimerHandle;
};
