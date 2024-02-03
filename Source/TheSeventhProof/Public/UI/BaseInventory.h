// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseInventory.generated.h"

UCLASS()
class THESEVENTHPROOF_API UBaseInventory : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
};
