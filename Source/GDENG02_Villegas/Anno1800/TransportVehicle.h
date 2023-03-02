// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvancedProductionBuilding.h"
#include "BasicProductionBuilding.h"
#include "TransportVehicle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_VILLEGAS_API UTransportVehicle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTransportVehicle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Vehicle Details
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vehicle") float TransportTime = 3.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle") float TransportTicks = 0.0f;
	UPROPERTY(EditAnywhere, Category = "Vehicle") int MaxCargo = 4;
	UPROPERTY(VisibleAnywhere, Category = "Vehicle") int CurrentCargo = 0;
	UPROPERTY(EditAnywhere, Category = "Cargo") bool TransportDone;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cargo") int Iron = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cargo") int Coal = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cargo") int Steel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cargo") int Wood = 0;

	// Vehicle Travel
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Travel") float TravelTime = 10.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Travel") float TravelTicks = 0.0f;
	UPROPERTY(VisibleAnywhere, Category = "Travel") AActor* CurrentDestination;
	UPROPERTY(VisibleAnywhere, Category = "Travel") AActor* NextDestination;
	UPROPERTY(VisibleAnywhere, Category = "Travel") FVector FromLocation;
	UPROPERTY(EditAnywhere, Category = "Travel") FVector ToLocation;
	UPROPERTY(EditAnywhere, Category = "Travel") bool HasArrived;

	// Buildings
	UPROPERTY(EditAnywhere, Category = "Buildings") AActor* GarageActor;
	UPROPERTY(EditAnywhere, Category = "Buildings") AActor* CoalMineActor;
	UPROPERTY(EditAnywhere, Category = "Buildings") AActor* IronMineActor;
	UPROPERTY(EditAnywhere, Category = "Buildings") AActor* FurnaceActor;
	UPROPERTY(EditAnywhere, Category = "Buildings") AActor* LumberjackHutActor;
	UPROPERTY(EditAnywhere, Category = "Buildings") AActor* SewingMachineFactoryActor;

	UPROPERTY(VisibleAnywhere) UBasicProductionBuilding* CoalMine;
	UPROPERTY(VisibleAnywhere) UBasicProductionBuilding* IronMine;
	UPROPERTY(VisibleAnywhere) UBasicProductionBuilding* LumberjackHut;
	UPROPERTY(VisibleAnywhere) UAdvancedProductionBuilding* Furnace;
	UPROPERTY(VisibleAnywhere) UAdvancedProductionBuilding* SewingMachineFactory;

	void SetDestination();
	bool LoadCargo();
	bool UnloadCargo();
	int CanDropoff();
};
