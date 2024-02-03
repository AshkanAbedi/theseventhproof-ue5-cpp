// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo

#pragma once

#pragma region Includes

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Objects/Inspectables.h"
#include "States/PlayerStates.h"
#include "PlayerCharacter.generated.h"

#pragma endregion Includes

#pragma region Forward Declarations

class USpringArmComponent;
class UCameraComponent;
class UCineCameraComponent;
class USpotLightComponent;
class UTimelineComponent;
class UPhysicalMaterial;
class UPostProcessComponent;
class UInputAction;
class AItems;
class AInspectables;
class AReads;

#pragma endregion Forward Declarations

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSeeingInteractableSignature, UClass*, InteractableType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractingSignature, AActor*, InteractedObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemAddedToInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCancelInput);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryInput);

UCLASS()
class THESEVENTHPROOF_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

#pragma region Getters&Setters

	[[nodiscard]] TArray<AItems*> GetInventory() const
	{
		return Inventory;
	}
	
#pragma endregion Getters&Setters

#pragma region Delegates
	
	UPROPERTY(BlueprintAssignable) FOnSeeingInteractableSignature OnSeeingInteractable;
	UPROPERTY(BlueprintAssignable) FOnInteractingSignature OnInteracting;
	UPROPERTY(BlueprintAssignable) FOnCancelInput OnCancelInputDelegate;
	UPROPERTY(BlueprintAssignable) FOnItemAddedToInventory OnItemAddedToInventoryDelegate;
	UPROPERTY(BlueprintAssignable) FOnInventoryInput OnInventoryInputDelegate;
	
#pragma endregion Delegates

#pragma region Main Components
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera") TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera") TObjectPtr<UCameraComponent> MainCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera") TObjectPtr<UCineCameraComponent> CineCamera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Flash Light") TObjectPtr<USpotLightComponent> FlashLight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "InspectableItem") TObjectPtr<USceneComponent> InspectableItem;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Timeline") TObjectPtr<UTimelineComponent> TimelineComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process") TObjectPtr<UPostProcessComponent> PostProcessComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player States") EPlayerState PlayerStates;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trace") TObjectPtr<AActor> TracedObject;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Trace") TObjectPtr<AActor> InteractedObject;

#pragma endregion Main Components

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma region Enhanced Input
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput") TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveForward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveBackward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveRight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputMoveLeft;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputLookAround;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputLookUp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputFlashLight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputInventory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputInteract;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputRotateItem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput") TObjectPtr<UInputAction> InputCancel;
	
#pragma endregion Enhanced Input
	
#pragma region Functions

	void MoveForward(const FInputActionValue& Value);
	void MoveBackward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void MoveLeft(const FInputActionValue& Value);
	void LookAround(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Inspect (const FInputActionValue& Value);
	void FlashLightToggle(const FInputActionInstance& Value);
	void InventoryToggle(const FInputActionInstance& Value);
	void TraceTimer();
	void Interact();
	void Cancel();
	UFUNCTION(BlueprintCallable) void OnCineCameraInitiate();
	UFUNCTION(BlueprintCallable) void OnCineCameraEnd();

#pragma endregion Functions

#pragma region Tracing
	FTimerHandle TraceTimerHandle;
	float TraceTimerCount = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace") float CameraTraceDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace") double FloorTraceDistance;
	TObjectPtr<UPhysicalMaterial> FloorPhysicalMaterial;
	bool bHitSomething;
	bool bHitFloor;
	FHitResult HitResult;
	FHitResult FloorHitResult;
	FCollisionQueryParams CameraTraceParams;
#pragma endregion Tracing

#pragma region Inventory

	friend class AItems;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory") TArray<AItems*> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory") int32 InventoryCapacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory") int32 InventoryCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory") int32 InventoryIndex;
	
	UFUNCTION(BlueprintCallable) void AddToInventory(AItems* Item);

#pragma endregion Inventory

#pragma region Inspection

	friend class AInspectables;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Inspection") TObjectPtr<AInspectables> InspectedObject;
	bool bInspection;

#pragma endregion Inspection

private:
	
};
