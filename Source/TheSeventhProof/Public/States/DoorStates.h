#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDoorStates : uint8
{
	EDS_StateNormal UMETA(DisplayName = "Normal"),
	EDS_StateLocked UMETA(DisplayName = "Locked"),
	EDS_StateUnlocking UMETA(DisplayName = "Unlocking"),
	
};
