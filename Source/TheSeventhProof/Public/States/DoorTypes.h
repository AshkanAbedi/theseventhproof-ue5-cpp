#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDoorTypes : uint8
{
	EDT_Type01 UMETA(DisplayName = "Rot on Yaw"),
	EDT_Type02 UMETA(DisplayName = "Rot on Roll"),
	EDT_Type03 UMETA(DisplayName = "Loc on X"),
	EDT_Type04 UMETA(DisplayName = "Loc on Y"),
	
};
