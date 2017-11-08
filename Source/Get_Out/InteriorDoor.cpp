// Ziad Hamdieh 2017

#include "InteriorDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"



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
	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();	// Set DefaultPawn (i.e. PlayerController) as actor that triggers door closure/opening
	OpenDoor();
}

void UInteriorDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, DoorCloseAngle, 0.f));
}

void UInteriorDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, DoorOpenAngle, 0.f));
}

// Called every frame
void UInteriorDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll The Pressure Plate Trigger Volume
	// If actor and pressure plate overlap (i.e. actor is inside the pressure plate), close the door
	if (DoorOpenPressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();		// set current time as the latest time that the door was open before getting closed
	}
	// Door Closing Delay
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime >= LastDoorOpenTime + DoorCloseDelay)
	{
		CloseDoor();
	}
}

