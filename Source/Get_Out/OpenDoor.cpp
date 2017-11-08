// Ziad Hamdieh 2017

#include "OpenDoor.h"
#include "Gameframework/Actor.h"


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

	AActor* Owner = GetOwner();									// Store memory address of door into Owner
	FRotator NewRotation = FRotator(0.f, -150.f, 0.f);				// Set yaw to close door
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor* Owner = GetOwner();									// Store memory address of door into Owner
	FRotator NewRotation = FRotator(0.f, -90.f, 0.f);				// Set yaw to close door
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll The Pressure Plate Trigger Volume
	// If actor and pressure plate overlap (i.e. actor is inside the pressure plate), close the door
	if (DoorClosePressurePlate->IsOverlappingActor(ActorThatCloses))
	{
		CloseDoor();
	}
}

