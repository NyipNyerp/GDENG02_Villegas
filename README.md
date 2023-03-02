# GDENG02_Villegas

GDENG02: Villegas, Hendrik Alexander A.
Unreal Challenge 1 - Anno 1800

Level/Map Name: Anno1800
Content Folder: Anno1800
C++ Classes Folder: Anno1800


C++ Classes:

Transport Vehicle [Actor Component] : Attached to both Transpo Vehicles. Used to transport produce between buildings
 - Functions:
	- void SetDestination() : Decides the Vehicle's next destination. 
	- bool LoadCargo() : Transfers the output products of buildings into the Vehicle. 
	- bool UnloadCargo() : Transfers the input products in the Vehicle into the buildings.
	- int CanDropOff() : Checks which buildings the Vehicle should go to, to UnloadCargo().

Basic Production Building [Actor Component] : Attached to CoalMine, IronMine, and LumberjackHut. Used to produce basic materials
	- bool PickupReady() : Simply checks if the building has produce ready for Loading.

Advanced Production Building [Actor Component] : Attached to Furnace and SewingMachineFactory. Used to produce advanced materials
	- bool PickupReady() : Simply checks if the building has produce ready for Loading.
	- Input1HasSpace() : Checks if the building's currentInput1 is not yet at max capacity.
	- Input2HasSpace() : Checks if the building's currentInput2 is not yet at max capacity.


Instructions:

1. Attach TransportVehicle component to both Transport Vehicles (PickupTrucks)
2. Attach BasicProductionBuilding component to CoalMine, IronMine, and LumberjackHut Actors in the Outliner
3. Attach AdvancedProductionBuilding component to Furnace and SewingMachineFactory Actors in the Outliner
4. Set the configurable data for all Actors that were assigned an ActorComponent in steps 1-3, in their respective Details Tab
5. Inside the TransportVehicles Details Tab, assign the references to all Buildings
6. Start Simulation.
