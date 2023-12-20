// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/BaseHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UBaseHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseHUD::HUDInterface_Implementation()
{
	if(IsValid(PromptText))
		PromptText->SetText(FText::FromString("This is an Observable!"));
}
