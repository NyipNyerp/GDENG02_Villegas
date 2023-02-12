// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinPusherController.h"

// Sets default values for this component's properties
UCoinPusherController::UCoinPusherController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCoinPusherController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCoinPusherController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	this->ticks += DeltaTime;

	if (this->ticks > this->INTERVAL)
	{
		this->ticks = 0.0f;
		this->movementY *= -1;
	}

	FVector location = this->snowmanPawn->GetTransform().GetLocation();
	location.Y += this->movementY * DeltaTime * this->SPEED_MULTIPLIER;
	this->snowmanPawn->SetActorLocation(location);
}

