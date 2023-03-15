// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Open door
	this->ticks += DeltaTime;
	if (this->GetPressurePlateTotalMass() >= this->totalMass && this->doorState == CLOSED)
	{
		this->ticks = 0.0f;
		this->doorState = OPEN;
	}
	else if (this->GetPressurePlateTotalMass() < this->totalMass && this->doorState == OPEN)
	{
		this->doorState = CLOSED;
	}
	
	if (this->doorState == OPEN)
	{
		this->currentYaw = FMath::Lerp(this->currentYaw, this->openingYaw, DeltaTime * 3.0f);

		FRotator doorRot = this->GetOwner()->GetActorRotation();
		doorRot.Yaw = this->currentYaw;
		this->GetOwner()->SetActorRotation(doorRot);
	}
	else if (this->doorState == CLOSED && this->ticks > 2.0f)
	{
		this->currentYaw = FMath::Lerp(this->currentYaw, this->closingYaw, DeltaTime * 1.0f);
		FRotator doorRot = this->GetOwner()->GetActorRotation();
		doorRot.Yaw = this->currentYaw;
		this->GetOwner()->SetActorRotation(doorRot);
	}
}

float UOpenDoor::GetPressurePlateTotalMass() const
{
	TArray<AActor*> actors;
	this->pressurePlate->GetOverlappingActors(actors);

	float mass = 0.0f;
	for (int i = 0; i < actors.Num(); i++)
	{
		UPrimitiveComponent* primitive = actors[i]->FindComponentByClass<UPrimitiveComponent>();
		mass += primitive->GetMass();
	}
	return mass;
}

