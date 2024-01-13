// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo
// ReSharper disable CppMemberFunctionMayBeConst
// ReSharper disable CppParameterMayBeConstPtrOrRef

#include "Character/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseUI.h"
#include "UI/BaseHUD.h"
#include "UI/BaseInventory.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


ABaseUI::ABaseUI()
{
	BaseHUDClass = nullptr;
	BaseHUD = nullptr;
	BaseInventoryClass = nullptr;
	TracedObjectClass = nullptr;
	InteractedObjectClass = nullptr;
}

void ABaseUI::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->OnSeeingInteractable.AddDynamic(this, &ABaseUI::OnSeeingInteractable);
	PlayerCharacter->OnInteracting.AddDynamic(this, &ABaseUI::OnInteracting);
	
	PlayerController = this->GetOwningPlayerController();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
	
	if (IsValid(BaseHUDClass))
	{
		BaseHUD = CreateWidget<UBaseHUD>(PlayerController, BaseHUDClass);
		BaseInventory = CreateWidget<UBaseInventory>(PlayerController, BaseInventoryClass);
		BaseHUD->AddToViewport();
		BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(5, 5));
	}
}

void ABaseUI::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABaseUI::OnSeeingInteractable(UClass* InteractableType)
{
	if (PlayerCharacter->PlayerStates == EPlayerState::EPS_Normal && PlayerCharacter->TracedObject->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
	{
		TracedObjectClass = PlayerCharacter->TracedObject->GetClass();

		switch (InteractableObjects.Find(TracedObjectClass))
		{
		case 0:
			BaseHUD->CrosshairIcons->SetBrushFromTexture(InteractableObjectIcons[0]);
			BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(40, 40));
			break;
			
		case 1:
			BaseHUD->CrosshairIcons->SetBrushFromTexture(InteractableObjectIcons[1]);
			BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(40, 40));
			break;

		case 2:
			BaseHUD->CrosshairIcons->SetBrushFromTexture(InteractableObjectIcons[2]);
			BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(40, 40));
			break;
			
		case 3:
			BaseHUD->CrosshairIcons->SetBrushFromTexture(InteractableObjectIcons[3]);
			BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(40, 40));
			break;
			
		case 4:
			BaseHUD->CrosshairIcons->SetBrushFromTexture(InteractableObjectIcons[4]);
			BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(40, 40));
			break;
			
		case 5:
			BaseHUD->CrosshairIcons->SetBrushFromTexture(InteractableObjectIcons[5]);
			BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(40, 40));
			break;
			
		default:
			break;
		}
	}
	else
	{
		BaseHUD->CrosshairIcons->SetBrushFromTexture(nullptr);
		BaseHUD->CrosshairIcons->SetDesiredSizeOverride(FVector2d(5, 5));
	}
}

void ABaseUI::OnInteracting(AActor* InteractedObject)
{
	if (PlayerCharacter->PlayerStates == EPlayerState::EPS_Normal)
	{
		InteractedObjectClass = InteractedObject->GetClass();

		switch (InteractableObjects.Find(InteractedObjectClass))
		{
		case 0:
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("THIS IS AN OBSERVABLE"));
			break;
			
		default:
			break;
		}
	}
}
