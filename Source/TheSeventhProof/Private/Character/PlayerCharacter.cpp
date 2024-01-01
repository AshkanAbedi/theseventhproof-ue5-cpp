// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppMemberFunctionMayBeConst
// ReSharper disable CppLocalVariableMayBeConst

#pragma region Includes

#include "Character/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Interfaces/InteractInterface.h"
#include "Objects/Inspectables.h"

#pragma  endregion Includes

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCapsuleHalfHeight(80.f);
	GetCapsuleComponent()->SetCapsuleRadius(32.f);
	GetMesh()->bCastFarShadow = true;
	GetMesh()->bCastVolumetricTranslucentShadow = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->SetRelativeLocation(FVector (0, 20, 160));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 8.f;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	MainCamera->SetupAttachment(CameraBoom);

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post Process Component"));
	PostProcessComponent->SetupAttachment(MainCamera);
	PostProcessComponent->bAutoActivate = true;

	InspectableItem = CreateDefaultSubobject<USceneComponent>(TEXT("Inspectable Item"));
	InspectableItem->SetupAttachment(MainCamera);

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flash Light"));
	FlashLight->SetupAttachment(MainCamera);

	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	CameraTraceParams.bReturnPhysicalMaterial = true;

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerStates = EPlayerState::EPS_Normal;
	GetWorld()->GetTimerManager().SetTimer(TraceTimerHandle, this, &APlayerCharacter::TraceTimer, TraceTimerCount, true);
}
void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(TraceTimerHandle);
}

#pragma region Movement

void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	if (PlayerStates == EPlayerState::EPS_Normal)
		AddMovementInput(FVector(GetActorForwardVector()), Value.GetMagnitude());
}

void APlayerCharacter::MoveBackward(const FInputActionValue& Value)
{
	if (PlayerStates == EPlayerState::EPS_Normal)
		AddMovementInput(FVector(GetActorForwardVector()) * -1.f, Value.GetMagnitude());
}

void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	if (PlayerStates == EPlayerState::EPS_Normal)	
		AddMovementInput(FVector(GetActorRightVector()), Value.GetMagnitude());
}

void APlayerCharacter::MoveLeft(const FInputActionValue& Value)
{
	if (PlayerStates == EPlayerState::EPS_Normal)
		AddMovementInput(FVector(GetActorRightVector()) * -1.f, Value.GetMagnitude());
}

void APlayerCharacter::LookAround(const FInputActionValue& Value)
{
	if ((Controller) && PlayerStates == EPlayerState::EPS_Normal)
		AddControllerYawInput(Value.GetMagnitude());
}

void APlayerCharacter::LookUp(const FInputActionValue& Value)
{
	if ((Controller) && PlayerStates == EPlayerState::EPS_Normal)
		AddControllerPitchInput(Value.GetMagnitude());
}

void APlayerCharacter::Inspect(const FInputActionValue& Value)
{
	if (IsValid(InspectedObject))
	{
		InspectedObject->StaticMeshComponent->AddWorldRotation(FRotator(Value.Get<FVector3d>().Z * InspectedObject->InspectRotateSpeed, Value.Get<FVector3d>().Y * InspectedObject->InspectRotateSpeed, Value.Get<FVector3d>().X * InspectedObject->InspectRotateSpeed));
	}
}

void APlayerCharacter::Cancel()
{
	if (PlayerStates == EPlayerState::EPS_Inspecting)
		InspectedObject->ReturnToStart();
	OnCancelInputDelegate.Broadcast();
}

#pragma endregion Movement
#pragma region Trace & Interact

void APlayerCharacter::TraceTimer()
{

	FVector ForwardTraceEndPoint = FVector(MainCamera->GetComponentLocation() + (MainCamera->GetForwardVector() * CameraTraceDistance));
	FVector FloorTraceEndPoint = FVector(MainCamera->GetComponentLocation().X, MainCamera->GetComponentLocation().Y, MainCamera->GetComponentLocation().Z - FloorTraceDistance);
	
	bHitSomething = GetWorld()->LineTraceSingleByChannel(HitResult, MainCamera->GetComponentLocation(), ForwardTraceEndPoint, ECC_Visibility, CameraTraceParams);
	bHitFloor = GetWorld()->LineTraceSingleByChannel(FloorHitResult, MainCamera->GetComponentLocation(), FloorTraceEndPoint, ECC_Visibility, CameraTraceParams);

	if (bHitSomething)
	{
		TracedObject = HitResult.GetActor();
		OnSeeingInteractable.Broadcast(HitResult.GetActor()->GetClass());
		// GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Hit Something: %s"), *TracedObject->GetName()));
	}

	if (bHitFloor)
	{
		FloorPhysicalMaterial = FloorHitResult.PhysMaterial.Get();
		if (!IsValid(FloorPhysicalMaterial))
			return;
		FString PhysicalMaterialName = FloorPhysicalMaterial->GetName();
		// GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Orange, FString::Printf(TEXT("Hit Floor: %s"), *PhysicalMaterialName));
	}
		
}

void APlayerCharacter::Interact()
{
	if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		OnInteracting.Broadcast(HitResult.GetActor());
		InteractedObject = HitResult.GetActor();
		IInteractInterface::Execute_Interact(HitResult.GetActor());
	}
}

#pragma endregion Trace & Interact
#pragma region Core Functions

void APlayerCharacter::FlashLightToggle(const FInputActionInstance& Value)
{
	FlashLight->ToggleVisibility();
}

void APlayerCharacter::AddToInventory(AItems* Item)
{
	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, TEXT("ADDING TO INVENTORY!"));
	
	if (InventoryCount < InventoryCapacity)
	{
		Inventory.Add(Item);
		InventoryCount++;
	}
}

#pragma endregion Core Functions

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Green, FString::Printf(TEXT("Player State: %s"), *UEnum::GetValueAsString(PlayerStates)));
}
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
	EnhancedInputComponent->BindAction(InputMoveBackward, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveBackward);
	EnhancedInputComponent->BindAction(InputMoveRight, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
	EnhancedInputComponent->BindAction(InputMoveLeft, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveLeft);
	EnhancedInputComponent->BindAction(InputLookAround, ETriggerEvent::Triggered, this, &APlayerCharacter::LookAround);
	EnhancedInputComponent->BindAction(InputLookUp, ETriggerEvent::Triggered, this, &APlayerCharacter::LookUp);
	EnhancedInputComponent->BindAction(InputFlashLight, ETriggerEvent::Triggered, this, &APlayerCharacter::FlashLightToggle);
	EnhancedInputComponent->BindAction(InputInteract, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
	EnhancedInputComponent->BindAction(InputRotateItem, ETriggerEvent::Triggered, this, &APlayerCharacter::Inspect);
	EnhancedInputComponent->BindAction(InputCancel, ETriggerEvent::Triggered, this, &APlayerCharacter::Cancel);
	
}



