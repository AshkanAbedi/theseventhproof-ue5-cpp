// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseInteractable.h"
#include "States/DoorTypes.h"
#include "States/DoorStates.h"
#include "States/ActorTags.h"
#include "Doors.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UTimelineComponent;
class UCurveFloat;
class UAudioComponent;
class USoundCue;
class APlayerCharacter;
class AItems;

UCLASS()
class THESEVENTHPROOF_API ADoors : public ABaseInteractable
{

	GENERATED_BODY()

public:
	ADoors();
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") EDoorStates DoorState;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components") TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UTimelineComponent> TimelineComponent;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<APlayerCharacter> PlayerCharacter;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> OpeningSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> ClosingSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> LockedSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<USoundCue> UnlockingSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<UCurveFloat> TogglingCurve;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") EDoorTypes DoorType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") EActorTags ActorTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components") TArray<AItems*> CorrespondingItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (MultiLine = true)) FText LockMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components") float MessageDuration;
	friend class APlayerCharacter;
	
	virtual void Interact_Implementation() override;
	virtual void BeginPlay() override;
	void OpeningDoor();
	void ClosingDoor();
	UFUNCTION() void Unlocking(AItems* Item);
	UFUNCTION() void DoorToggling(const float Output) const;
	UFUNCTION() void TimelineFinished();
	FTimerHandle UnlockTimerHandle;

private:
	bool bIsOpen = false;
	bool bIsToggling = false;

public:
#pragma region Getters&Setters

	[[nodiscard]] TArray<AItems*> GetCorrespondingItems() const
	{
		return CorrespondingItems;
	}
	
#pragma endregion Getters&Setters
	
};
