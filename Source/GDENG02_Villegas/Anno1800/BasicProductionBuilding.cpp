// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProductionBuilding.h"

// Sets default values for this component's properties
UBasicProductionBuilding::UBasicProductionBuilding()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBasicProductionBuilding::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBasicProductionBuilding::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// PRODUCTION
	if (this->currentOutput < this->maxOutput) // Check if products storage is full
	{
		this->ticks += DeltaTime;
		if (this->ticks >= this->productionTime) // If not, start making products
		{
			this->currentOutput += this->productionAmount;
			if (this->currentOutput > this->maxOutput) // If the number of made products exceed storage limit, discard excess products
				this->currentOutput = this->maxOutput;
			this->ticks = 0;
		}
	}
}

bool UBasicProductionBuilding::PickupReady()
{
	return this->currentOutput > 0;
}

