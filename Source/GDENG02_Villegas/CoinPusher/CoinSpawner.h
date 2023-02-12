// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_VILLEGAS_API UCoinSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoinSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere) AActor* actorCopy = NULL;
	UPROPERTY(EditAnywhere) int spawnLimit = 30;
	float ticks = 0.0f;
	float destroyTicks = 0.0f;
	float INTERVAL = 1.0f;
	float DELETE_INTERVAL = 30.0f;

	TArray<AActor*> spawnedObjects;

	void DeleteAll();
};
