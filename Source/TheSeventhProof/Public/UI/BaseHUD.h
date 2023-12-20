// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/HUDInterface.h"
#include "BaseHUD.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class THESEVENTHPROOF_API UBaseHUD : public UUserWidget, public IHUDInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void HUDInterface_Implementation() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UImage> CrosshairIcons;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> PromptText;
};
