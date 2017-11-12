// Ziad Hamdieh 2017

#include "ExteriorDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"



// Sets default values for this component's properties
UExteriorDoor::UExteriorDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UExteriorDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();															// Get owner of this script
	ActorThatClosesDoor = GetWorld()->GetFirstPlayerController()->GetPawn();	// Set DefaultPawn (i.e. PlayerController) as actor that triggers door closure/opening
	Owner->SetActorRotation(FRotator(0.f, InitialDoorAngle, 0.f));
}

// Called every frame
void UExteriorDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll The Pressure Plate Trigger Volume
	// If actor and pressure plate overlap (i.e. actor is inside the pressure plate), close the door
	if (DoorClosePressurePlate->IsOverlappingActor(ActorThatClosesDoor))
	{
		OnCloseRequest.Broadcast();
	}
}

