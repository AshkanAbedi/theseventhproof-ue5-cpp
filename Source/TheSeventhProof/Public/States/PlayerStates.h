#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	EPS_Normal UMETA(DisplayName = "Normal"),
	EPS_Seeing UMETA(DisplayName = "Seeing"),
	EPS_Interacting UMETA(DisplayName = "Interacting"),
	EPS_Inspecting UMETA(DisplayName = "Inspecting"),
	EPS_Talking UMETA(DisplayName = "Talking")
};