// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VMTime.generated.h"

UCLASS(BlueprintType)
class THESEVENTHPROOF_API UVMTime : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	float GetTime() const { return Time; }

	UFUNCTION(BlueprintCallable)
	void SetTime(const float NewTime) { Time = NewTime; }

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetTimePercent() const { return Time / TotalTime; }

private:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess)) float Time;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess)) float TotalTime;
};
