// Ziad Hamdieh 2017

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"



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

	Owner = GetOwner();															// Get owner of this script
	ActorThatClosesDoor = GetWorld()->GetFirstPlayerController()->GetPawn();	// Set DefaultPawn (i.e. PlayerController) as actor that triggers door closure/opening
	OpenDoor();
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, DoorCloseAngle, 0.f));
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, DoorOpenAngle, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll The Pressure Plate Trigger Volume
	// If actor and pressure plate overlap (i.e. actor is inside the pressure plate), close the door
	if (DoorClosePressurePlate->IsOverlappingActor(ActorThatClosesDoor))
	{
		CloseDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();		// set current time as the latest time that the door was open before getting closed
	}
	// Door Closing Delay
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime >= LastDoorOpenTime + DoorCloseDelay) 
	{
		OpenDoor();
	}
}

