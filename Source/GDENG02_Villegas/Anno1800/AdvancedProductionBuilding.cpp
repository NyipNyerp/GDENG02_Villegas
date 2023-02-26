// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedProductionBuilding.h"

// Sets default values for this component's properties
UAdvancedProductionBuilding::UAdvancedProductionBuilding()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAdvancedProductionBuilding::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAdvancedProductionBuilding::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// PRODUCTION
	if (this->currentOutput < this->maxOutput) // Check if products storage is full
	{
		if (this->currentInput_1 > 0 && this->currentInput_2 > 0) // Check if building has enough ingredients to make products
		{
			this->ticks += DeltaTime;
			if (this->ticks >= this->productionTime) // If so, start making products
			{
				this->currentOutput += this->productionAmount;
				this->currentInput_1 -= this->productionAmount;
				this->currentInput_2 -= this->productionAmount;
				if (this->currentOutput > this->maxOutput) // If the number of made products exceed storage limit, discard excess products
					this->currentOutput = this->maxOutput;
				this->ticks = 0;
			}
		}
	}
}

bool UAdvancedProductionBuilding::PickupReady()
{
	return this->currentOutput > 0;
}

bool UAdvancedProductionBuilding::Input1HasSpace()
{
	return this->currentInput_1 < this->maxInput_1;
}

bool UAdvancedProductionBuilding::Input2HasSpace()
{
	return this->currentInput_2 < this->maxInput_2;
}

