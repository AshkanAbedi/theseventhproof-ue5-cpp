#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EKeyNames : uint8
{
	EKN_None UMETA(DisplayName = "None"),
	EKN_Key1 UMETA(DisplayName = "Bedroom Key"),
	EKN_Key2 UMETA(DisplayName = "Bathroom Key"),
	
};
