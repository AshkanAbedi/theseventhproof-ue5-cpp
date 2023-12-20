// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineTraceComponent.generated.h"

class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THESEVENTHPROOF_API ULineTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULineTraceComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FTimerHandle TraceTimerHandle;
	float TraceTimerCount = 0.016;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace") float TraceDistance = 500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trace") TObjectPtr<UCameraComponent> Source;
	bool bHitSomething = false;
	FHitResult HitResult;
	FCollisionQueryParams TraceParams;

	void TraceTimer();

private:	
	
		
};
