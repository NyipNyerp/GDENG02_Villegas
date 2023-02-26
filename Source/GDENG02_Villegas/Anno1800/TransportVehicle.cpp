// Fill out your copyright notice in the Description page of Project Settings.


#include "TransportVehicle.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTransportVehicle::UTransportVehicle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTransportVehicle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->CoalMine = this->CoalMineActor->FindComponentByClass<UBasicProductionBuilding>();
	this->IronMine = this->IronMineActor->FindComponentByClass<UBasicProductionBuilding>();
	this->Furnace = this->FurnaceActor->FindComponentByClass<UAdvancedProductionBuilding>();
	this->LumberjackHut = this->LumberjackHutActor->FindComponentByClass<UBasicProductionBuilding>();
	this->SewingMachineFactory = this->SewingMachineFactoryActor->FindComponentByClass<UAdvancedProductionBuilding>();

	this->FromLocation = this->GetOwner()->GetActorLocation();
	this->CurrentDestination = this->GarageActor;
	this->SetDestination();
	this->CurrentCargo = this->Iron + this->Coal + this->Steel + this->Wood;
	//this->ToLocation = this->LumberjackHutActor->GetActorLocation();
}


// Called every frame
void UTransportVehicle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	this->SetDestination();

	// Vehicle moves to next destination when ready
	if (this->TravelTicks < this->TravelTime && !this->HasArrived)
	{
		this->TravelTicks += DeltaTime;
		this->GetOwner()->SetActorLocation(FMath::Lerp(this->FromLocation, this->ToLocation, this->TravelTicks / this->TravelTime));
		this->GetOwner()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(this->FromLocation, this->ToLocation));
		//UE_LOG(LogTemp, Warning, TEXT("Travelling to destination..."));
	}
	// Vehicle has arrived at destination. Begin cargo transportation
	else if (!this->HasArrived)
	{
		this->GetOwner()->SetActorLocation(this->ToLocation);
		this->FromLocation = this->GetOwner()->GetActorLocation();

		/*if (this->CurrentCargo > 0)
		{
			this->UnloadCargo();
			this->TransportDone = false;
		}
		this->LoadCargo();
		this->CurrentCargo = this->Iron + this->Coal + this->Steel + this->Wood;*/

		if (!this->UnloadCargo() || !this->LoadCargo())
			this->TransportDone = false;
		this->CurrentCargo = this->Iron + this->Coal + this->Steel + this->Wood;
		
		this->HasArrived = true;
		this->TravelTicks = 0;
		//UE_LOG(LogTemp, Warning, TEXT("Arrived at destination..."));
	}

	// Vehicle waits in destination until cargo transportation is done
	if (this->TransportTicks < this->TransportTime && this->HasArrived)
	{
		this->TransportTicks += DeltaTime;
		if (this->CurrentCargo <= 0 && this->TransportDone)
			this->TransportTicks += this->TransportTime;
		//UE_LOG(LogTemp, Warning, TEXT("Loading/Unloading cargo..."));
	}
	// Cargo transportation is done. Checking for new destination
	else if (this->HasArrived)
	{
		this->TransportTicks = 0;
		this->TransportDone = true;
		this->SetDestination();
		this->HasArrived = false;
		//UE_LOG(LogTemp, Warning, TEXT("Looking for new destination..."));
	}
}

void UTransportVehicle::SetDestination()
{
	// IF VEHICLE HAS CARGO AND CAN DROP OFF CURRENT CARGO, SET DESTINATION FOR DELIVERY TO RESPECTIVE BUILDINGS
	if (this->CurrentCargo > 0 && CanDropoff() != 0)
	{
		switch (CanDropoff()) {
		case 1: // If steel or wood can be dropped off
			this->NextDestination = this->SewingMachineFactoryActor;
			break;
		case 2: // If coal or iron can be dropped off
			this->NextDestination = this->FurnaceActor;
			break;
		}
	}
	// IF VEHICLE HAS NO CARGO OR CANT DROP OFF CURRENT CARGO, CHECK WHICH BUILDINGS ARE READY FOR PICKUP AND WHICH RESOURCES ARE NEEDED
	else
	{
		// If steel can be picked up & is needed
		if (this->Furnace->PickupReady() && this->SewingMachineFactory->currentInput_1 < this->SewingMachineFactory->maxInput_1)
			this->NextDestination = this->FurnaceActor;
		// If wood can be picked up & is needed
		else if (this->LumberjackHut->PickupReady() && this->SewingMachineFactory->currentInput_2 < this->SewingMachineFactory->maxInput_2)
			this->NextDestination = this->LumberjackHutActor;
		// If coal can be picked up & is needed
		else if (this->CoalMine->PickupReady() && this->Furnace->currentInput_1 < this->Furnace->maxInput_1)
			this->NextDestination = this->CoalMineActor;
		// If iron can be picked up & is needed
		else if (this->IronMine->PickupReady() && this->Furnace->currentInput_2 < this->Furnace->maxInput_2)
			this->NextDestination = this->IronMineActor;

		// IF THERE ARE NO BUILDINGS READY FOR PICKUP OR IN NEED OF RESOURCES, SET DESTINATION TO GARAGE
		else this->NextDestination = this->GarageActor;
	}
	
	// IF VEHICLE HAS ARRIVED AND CARGO TRANSPORTATION IS DONE, HEAD TO NEXT DESTINATION
	if (this->HasArrived && this->TransportDone)
	{
		this->CurrentDestination = this->NextDestination;
		this->ToLocation = this->CurrentDestination->GetActorLocation();
	}
}

bool UTransportVehicle::LoadCargo()
{
	bool result = true;
	// CHECK IF VEHICLE CAN STILL CARRY CARGO. IF SO, CHECK CURRENT DESTINATION TO FIGURE OUT WHICH BUILDING TO LOAD CARGO FROM
	if (this->CurrentCargo < this->MaxCargo)
	{
		if (this->CurrentDestination == this->CoalMineActor)
		{
			for (int i = 0; i < this->MaxCargo - this->CurrentCargo; i++)
			{
				if (this->CoalMine->PickupReady())
				{
					this->CoalMine->currentOutput--;
					this->Coal++;
					result = false;
				}
			}
		}
		else if (this->CurrentDestination == this->IronMineActor)
		{
			for (int i = 0; i < this->MaxCargo - this->CurrentCargo; i++)
			{
				if (this->IronMine->PickupReady())
				{
					this->IronMine->currentOutput--;
					this->Iron++;
					result = false;
				}
			}
		}
		else if (this->CurrentDestination == this->FurnaceActor)
		{
			for (int i = 0; i < this->MaxCargo - this->CurrentCargo; i++)
			{
				if (this->Furnace->PickupReady())
				{
					this->Furnace->currentOutput--;
					this->Steel++;
					result = false;
				}
			}
		}
		else if (this->CurrentDestination == this->LumberjackHutActor)
		{
			for (int i = 0; i < this->MaxCargo - this->CurrentCargo; i++)
			{
				if (this->LumberjackHut->PickupReady())
				{
					this->LumberjackHut->currentOutput--;
					this->Wood++;
					result = false;
				}
			}
		}
	}
	return result;
}

bool UTransportVehicle::UnloadCargo()
{
	bool result = true;
	// CHECK IF VEHICLE HAS ANY CARGO. IF SO, CHECK IF DROP OFF AT CURRENT DESTINATION IS POSSIBLE
	if (this->CurrentCargo > 0)
	{
		if (this->CurrentDestination == this->SewingMachineFactoryActor)
		{
			while (this->Steel > 0 && this->SewingMachineFactory->currentInput_1 < this->SewingMachineFactory->maxInput_1)
			{
				this->Steel--;
				this->SewingMachineFactory->currentInput_1++;
				result = false;
			}
			while (this->Wood > 0 && this->SewingMachineFactory->currentInput_2 < this->SewingMachineFactory->maxInput_2)
			{
				this->Wood--;
				this->SewingMachineFactory->currentInput_2++;
				result = false;
			}
		}
		else if (this->CurrentDestination == this->FurnaceActor)
		{
			while (this->Coal > 0 && this->Furnace->currentInput_1 < this->Furnace->maxInput_1)
			{
				this->Coal--;
				this->Furnace->currentInput_1++;
				result = false;
			}
			while (this->Iron > 0 && this->Furnace->currentInput_2 < this->Furnace->maxInput_2)
			{
				this->Iron--;
				this->Furnace->currentInput_2++;
				result = false;
			}
		}
	}
	return result;
}

int UTransportVehicle::CanDropoff()
{
	int result = 0;
	if (this->Steel > 0 && this->SewingMachineFactory->Input1HasSpace() || this->Wood > 0 && this->SewingMachineFactory->Input2HasSpace()) result = 1;
	else if (this->Coal > 0 && this->Furnace->Input1HasSpace() || this->Iron > 0 && this->Furnace->Input2HasSpace()) result = 2;
	return result;
}

