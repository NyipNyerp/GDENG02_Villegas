// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSpawner.h"

// Sets default values for this component's properties
UCoinSpawner::UCoinSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCoinSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->actorCopy->SetActorHiddenInGame(true);
}


// Called every frame
void UCoinSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	this->ticks += DeltaTime;
	this->destroyTicks += DeltaTime;

	if (this->ticks > this->INTERVAL)
	{
		this->ticks = 0.0f;
		// spawn object
		if (this->actorCopy != NULL && this->spawnedObjects.Num() < this->spawnLimit)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Template = this->actorCopy;
			spawnParams.Owner = this->GetOwner();

			FVector soawnLoc = this->GetOwner()->GetActorLocation();
			FRotator spawnRot = this->GetOwner()->GetActorRotation();

			AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->actorCopy->GetClass(), spawnParams);
			myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
			myActor->SetActorHiddenInGame(false);
			myActor->SetActorLocation(soawnLoc);
			myActor->SetActorRotation(spawnRot);

			this->spawnedObjects.Add(myActor);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Actor is null. Will not spawn."));
		}

		if (this->destroyTicks > this->DELETE_INTERVAL)
		{
			this->destroyTicks = 0.0f;
			this->DeleteAll();
		}
	}
}

void UCoinSpawner::DeleteAll()
{
	UE_LOG(LogTemp, Display, TEXT("Destroying all coins."));
	for (int i = 0; i < this->spawnedObjects.Num(); i++)
	{
		this->spawnedObjects[i]->Destroy();
	}
	this->spawnedObjects.Reset();
}

