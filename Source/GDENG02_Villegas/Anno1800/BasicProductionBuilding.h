// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicProductionBuilding.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_VILLEGAS_API UBasicProductionBuilding : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasicProductionBuilding();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool PickupReady();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly) FString outputName; // Product name
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int maxOutput = 3; // Number of goods the building can store at a time
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int currentOutput = 0; // Number of goods the building has
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float productionTime = 5.0f; // Time needed to produce goods
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int productionAmount = 1; // Number of goods produced per cycle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float ticks = 0.0f;
};
