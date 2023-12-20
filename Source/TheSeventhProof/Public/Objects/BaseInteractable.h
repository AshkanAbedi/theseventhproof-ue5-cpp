// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable IdentifierTypo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "BaseInteractable.generated.h"

class APlayerCharacter;

UCLASS()
class THESEVENTHPROOF_API ABaseInteractable : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ABaseInteractable();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

protected:
	virtual void BeginPlay() override;

private:	
	
};
