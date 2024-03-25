// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUD.generated.h"

class UOverlay;
class UImage;
class UTextBlock;
class UVerticalBox;
class UBorder;
class UBackgroundBlur;
class USizeBox;
class UProgressBar;
class UVMTime;

UCLASS()
class THESEVENTHPROOF_API UBaseHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UOverlay> Overlay;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UImage> CrosshairIcons;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> PromptText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UVerticalBox> QuestList;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> Task01;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UTextBlock> Task02;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UBorder> Border;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UBackgroundBlur> BackgroundBlur;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UImage> ReadingImage;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<USizeBox> SizeBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) TObjectPtr<UProgressBar> TimeBar;
};
