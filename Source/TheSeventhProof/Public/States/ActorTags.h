#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EActorTags : uint8
{
	EAT_Doors UMETA(DisplayName = "Doors"),
	EAT_Inspectables UMETA(DisplayName = "Inspectables"),
	EAT_Items UMETA(DisplayName = "Items"),
	EAT_Lights UMETA(DisplayName = "Lights"),
	EAT_Observables UMETA(DisplayName = "Observables"),
	EAT_Reads UMETA(DisplayName = "Reads"),
};
