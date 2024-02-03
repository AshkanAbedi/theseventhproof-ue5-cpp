// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo
// ReSharper disable CppMemberFunctionMayBeConst
// ReSharper disable CppParameterMayBeConstPtrOrRef
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement

#include "Character/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BaseUI.h"
#include "UI/BaseHUD.h"
#include "UI/BaseInventory.h"
#include "Blueprint/UserWidget.h"
#include "Components/BackgroundBlur.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Objects/Doors.h"
#include "Objects/Observables.h"
#include "Objects/Reads.h"

ABaseUI::ABaseUI()
{
	BaseHUDClass = nullptr;
	BaseHUD = nullptr;
	BaseInventoryClass = nullptr;
	TracedObjectClass = nullptr;
	InteractedObjectClass = nullptr;
	Observable = nullptr;
}

void ABaseUI::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCharacter->OnSeeingInteractable.AddDynamic(this, &ABaseUI::OnSeeingInteractable);
	PlayerCharacter->OnInteracting.AddDynamic(this, &ABaseUI::OnInteracting);
	PlayerCharacter->OnCancelInputDelegate.AddDynamic(this, &ABaseUI::OnCancelInput);
	PlayerCharacter->OnInventoryInputDelegate.AddDynamic(this, &ABaseUI::OnInventoryInput);
	
	PlayerController = this->GetOwningPlayerController();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
	
	if (IsValid(BaseHUDClass))
	{
		BaseHUD = CreateWidget<UBaseHUD>(PlayerController, BaseHUDClass);
		BaseInventory = CreateWidget<UBaseInventory>(PlayerController, BaseInventoryClass);
		BaseHUD->AddToViewport();
		ClearCrosshairIcon();
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
			SetCrosshairIcon(0, FVector2d(40, 40));
			break;
			
		case 1:
			SetCrosshairIcon(1, FVector2d(40, 40));
			break;

		case 2:
			SetCrosshairIcon(2, FVector2d(40, 40));
			break;
			
		case 3:
			SetCrosshairIcon(3, FVector2d(40, 40));
			break;
			
		case 4:
			SetCrosshairIcon(4, FVector2d(40, 40));
			break;
			
		case 5:
			SetCrosshairIcon(5, FVector2d(40, 40));
			break;
			
		default:
			break;
		}
	}
	else
	{
		ClearCrosshairIcon();
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
			Observable = Cast<AObservables>(InteractedObject);
			if (IsValid(Observable))
				SetPromptText(Observable->GetStoryText(), Observable->GetStoryDelay());
			break;
			
		case 1:
			Door = Cast<ADoors>(InteractedObject);
			if (IsValid(Door))
				switch (Door->DoorState)
				{
					case EDoorStates::EDS_StateLocked:
						SetPromptText(Door->GetLockMessage(), Door->GetMessageDuration());
					break;

					case EDoorStates::EDS_StateUnlocking:
						ClearPromptText();
					break;

					case EDoorStates::EDS_StateNormal:
						ClearPromptText();
					break;
				}
			break;
	
		case 2:
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Item")));
			break;
			
		case 3:
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Light")));
			break;
			
		case 4:
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Inspectable")));
			ClearCrosshairIcon();
			break;
			
		case 5:
			GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Read")));
			Read = Cast<AReads>(InteractedObject);
			if (IsValid(Read))
				SetReadingImage(Read->GetReadImage());
			break;
			
		default:
			break;
		}
	}
}

void ABaseUI::SetCrosshairIcon(const int Index, const FVector2d Size)
{
	BaseHUD->CrosshairIcons->SetVisibility(ESlateVisibility::Visible);
	BaseHUD->CrosshairIcons->SetBrushFromTexture(InteractableObjectIcons[Index]);
	BaseHUD->CrosshairIcons->SetDesiredSizeOverride(Size);
}

void ABaseUI::ClearCrosshairIcon()
{
	BaseHUD->CrosshairIcons->SetVisibility(ESlateVisibility::Hidden);
}

void ABaseUI::SetPromptText(const FText& Text, const float Duration)
{
	BaseHUD->PromptText->SetText(Text);
	GetWorld()->GetTimerManager().SetTimer(TextTimerHandle, this, &ABaseUI::ClearPromptText, Duration, false);
}

void ABaseUI::ClearPromptText()
{
	BaseHUD->PromptText->SetText(FText::FromString(""));
	GetWorld()->GetTimerManager().ClearTimer(TextTimerHandle);
}

void ABaseUI::SetReadingImage(UTexture2D* Image)
{
	BaseHUD->ReadingImage->SetBrushFromTexture(Image, false);
	BaseHUD->ReadingImage->Brush.DrawAs = ESlateBrushDrawType::Image;
	BaseHUD->ReadingImage->Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 1.f);
	BaseHUD->BackgroundBlur->SetBlurStrength(5.f);
}

void ABaseUI::ClearReadingImage()
{
	BaseHUD->ReadingImage->SetBrushFromTexture(nullptr);
	BaseHUD->ReadingImage->Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
	BaseHUD->BackgroundBlur->SetBlurStrength(0.f);
}

void ABaseUI::OnCancelInput()
{
	ClearReadingImage();
	BaseHUD->CrosshairIcons->SetVisibility(ESlateVisibility::Visible);
}

void ABaseUI::OnInventoryInput()
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Inventory Input")));
	
	if (!bInventoryPanel)
	{
		BaseInventory->AddToViewport();
		BaseHUD->RemoveFromParent();
		PlayerController->SetInputMode(FInputModeGameAndUI());
		bInventoryPanel = true;
	}
	else
	{
		BaseInventory->RemoveFromParent();
		BaseHUD->AddToViewport();
		PlayerController->SetInputMode(FInputModeGameOnly());
		bInventoryPanel = false;
	}
}
