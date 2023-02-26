// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvancedProductionBuilding.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_VILLEGAS_API UAdvancedProductionBuilding : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAdvancedProductionBuilding();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool PickupReady();
	bool Input1HasSpace();
	bool Input2HasSpace();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly) FString inputName_1; // Ingredient name
	//UPROPERTY(EditAnywhere, BlueprintReadOnly) FString inputName_2; // Ingredient name
	//UPROPERTY(EditAnywhere, BlueprintReadOnly) FString outputName; // Product name

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int maxInput_1 = 3; // Number of ingredients the building can store at a time
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int maxInput_2 = 3; // Number of ingredients the building can store at a time
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int maxOutput = 3; // Number of products the building can store at a time

	UPROPERTY(EditAnywhere, BlueprintReadOnly) int currentInput_1 = 0; // Number of ingredients the building has
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int currentInput_2 = 0; // Number of ingredients the building has
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int currentOutput = 0; // Number of products the building has

	UPROPERTY(EditAnywhere, BlueprintReadOnly) float productionTime = 5.0f; // Time needed to make products
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int productionAmount = 1; // Number of products made per cycle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) float ticks = 0.0f;
};
