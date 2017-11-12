// Ziad Hamdieh 2017

#include "InteriorDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UInteriorDoor::UInteriorDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInteriorDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();															// Get owner of this script
}

// Called every frame
void UInteriorDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll The Pressure Plate Trigger Volume
	if (GetMassOnPlate() > MinimumMassToOpenDoor)				// If actor and pressure plate overlap (i.e. actor is inside the pressure plate), close the door
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}

float UInteriorDoor::GetMassOnPlate()
{
	TArray<AActor*> ActorsCurrentlyOnPlate;

	float TotalMass = 0.f;										// set TotalMass to 0 so that any amount of mass on pressure plate will cause door to open
	if (!DoorOpenPressurePlate) return TotalMass;
	DoorOpenPressurePlate->GetOverlappingActors(OUT ActorsCurrentlyOnPlate);
	for (const auto* Actor : ActorsCurrentlyOnPlate) {			// Iterate through TArray using a range-based for loop (recommended type of loop by UE4 standards)
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

