// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayManager.generated.h"

class USceneComponent;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components") TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TObjectPtr<APlayerCharacter> PlayerCharacter;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TArray<AActor*> ItemActors;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components") TArray<AActor*> DoorsActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TArray<AItems*> Items;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") TArray<ADoors*> Doors;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:	
	
};
