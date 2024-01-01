#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemNames : uint8
{
	EIN_None UMETA(DisplayName = "NONE"),
	EIN_Item01 UMETA(DisplayName = "BEDROOM KEY"),
	EIN_Item02 UMETA(DisplayName = "BATHROOM KEY"),
	EIN_Item03 UMETA(DisplayName = "LOCK PIN"),
};
