// Ziad Hamdieh 2017

#include "ObjectGrabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UObjectGrabber::UObjectGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectGrabber::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UObjectGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,							
		PlayerViewPointRotation
	);

	UE_LOG(LogTemp, Warning, TEXT("Player's Location: %s, Looking: %s"),
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotation.ToString()
	)
}

