// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayManager.generated.h"

class APlayerCharacter;
class AItems;
class ADoors;
class AInspectables;
class AReads;
class ALights;
class AObservables;


UCLASS()
class THESEVENTHPROOF_API AGameplayManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameplayManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:	
	
};
